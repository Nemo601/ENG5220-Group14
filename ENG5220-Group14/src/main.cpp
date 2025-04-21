#include "../include/yolo_detector.h"
#include "../include/GarbageSorter.h"
#include "../include/Timer.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <filesystem>
#include <iostream>
#include <atomic>
#include <csignal>
#include <wiringPi.h>
#include <thread>
#include <mutex>
#include <unordered_map>
#include "../include/CameraWorker.h"

std::atomic<bool> running(true);
std::shared_ptr<std::vector<Object>> latest_result;
std::mutex latest_mutex;
namespace fs = std::filesystem;

bool image_exists = false;

void signalHandler(int) {
    running = false;
    std::cout << "\n[系统] 收到退出信号 (Ctrl+C)，准备退出...\n";
}

bool hasImageInDirectory(const std::string& path) {
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            std::string ext = entry.path().extension().string();
            if (ext == ".jpg" || ext == ".png" || ext == ".jpeg" || ext == ".bmp") {
                return true;
            }
        }
    }
    return false;
}

int main() {
    const std::string watch_path = "/home/pi/ENG5220/image";
    std::unordered_map<int, int> label_to_category = {
        {0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}, {8, 3}, {9, 1},
        {10, 1}, {11, 1}, {12, 1}, {13, 1}, {14, 3}, {15, 3}, {16, 3}, {17, 3}, {18, 3}, {19, 3},
        {20, 3}, {21, 3}, {22, 3}, {23, 3}, {24, 1}, {25, 1}, {26, 1}, {27, 1}, {28, 1}, {29, 1},
        {30, 1}, {31, 1}, {32, 1}, {33, 1}, {34, 1}, {35, 1}, {36, 1}, {37, 1}, {38, 1}, {39, 1},
        {40, 1}, {41, 1}, {42, 1}, {43, 1}, {44, 1}, {45, 1}, {46, 2}, {47, 2}, {48, 2}, {49, 2},
        {50, 2}, {51, 2}, {52, 2}, {53, 2}, {54, 2}, {55, 2}, {56, 1}, {57, 1}, {58, 3}, {59, 1},
        {60, 1}, {61, 4}, {62, 1}, {63, 1}, {64, 4}, {65, 4}, {66, 4}, {67, 1}, {68, 1}, {69, 1},
        {70, 1}, {71, 1}, {72, 1}, {73, 4}, {74, 1}, {75, 4}, {76, 4}, {77, 4}, {78, 4}, {79, 4}
    };

    wiringPiSetupGpio();
    const int SENSOR_PIN = 25;
    pinMode(SENSOR_PIN, INPUT);
    pullUpDnControl(SENSOR_PIN, PUD_UP);
    signal(SIGINT, signalHandler);

    std::cout << "等待光电传感器触发..." << std::endl;
    while (digitalRead(SENSOR_PIN) == HIGH && running) {
        std::this_thread::yield();
    }
    if (!running) {
        std::cout << "启动前被中断，退出。\n";
        return 0;
    }
    std::cout << "物体检测到，系统启动！" << std::endl;

    CameraWorker cw;
    cw.start();
    startTimerThread();
    signal(SIGINT, signalHandler);  // 再次注册

    std::vector<std::vector<int>> motorPins = {
        {4, 17, 23, 24}, {5, 6, 12, 13}, {16, 20, 21, 26}, {18, 19, 22, 27}
    };
    GarbageSorter sorter(motorPins);
    sorter.setStatusCallback([](const std::string& msg) {
        std::cout << "[系统状态] " << msg << std::endl;
    });
    sorter.startSystem();

    YoloDetector detector;
    if (!detector.loadModel("/home/pi/ENG5220/weights/yolov5s_6.0.param", "/home/pi/ENG5220/weights/yolov5s_6.0.bin")) {
        std::cerr << "模型加载失败。" << std::endl;
        return -1;
    }

    detector.setCallback([](const std::vector<Object>& objs) {
        std::lock_guard<std::mutex> lock(latest_mutex);
        latest_result = std::make_shared<std::vector<Object>>(objs);
        std::cout << "检测到 " << objs.size() << " 个目标。" << std::endl;
    });

    // 定时检查图片
    IntervalTimer checkImageTimer;
    checkImageTimer.setInterval([&]() {
        bool now_has_image = hasImageInDirectory(watch_path);

        if (now_has_image && !image_exists) {
            std::cout << "[事件] 检测到新图片，启动识别线程。" << std::endl;
            std::thread detect_thread([&detector, &watch_path]() {
                for (const auto& entry : fs::directory_iterator(watch_path)) {
                    std::string ext = entry.path().extension().string();
                    if (ext == ".jpg" || ext == ".png" || ext == ".jpeg" || ext == ".bmp") {
                        cv::Mat img = cv::imread(entry.path().string());
                        if (!img.empty()) {
                            detector.detect(img);
                            fs::remove(entry.path());
                        }
                    }
                }
            });
            detect_thread.detach();
        }

        if (!now_has_image && image_exists) {
            std::cout << "[事件] 目录无图片，终止识别行为。" << std::endl;
        }

        image_exists = now_has_image;

        std::shared_ptr<std::vector<Object>> local_copy;
        {
            std::lock_guard<std::mutex> lock(latest_mutex);
            if (latest_result && !latest_result->empty()) {
                local_copy = latest_result;
                latest_result.reset();  // ⚠️ 清除以避免重复处理
            }
        }

        if (local_copy) {
            std::thread motor_thread([local_copy, &sorter, &label_to_category]() {
                for (const auto& obj : *local_copy) {
                    int label = obj.label;
                    auto it = label_to_category.find(label);
                    if (it != label_to_category.end()) {
                        int category = it->second;
                        std::cout << "目标编号 " << label << " 匹配分类: " << category << std::endl;
                        sorter.processWaste(static_cast<GarbageSorter::WasteType>(category));
                        sorter.waitUntilIdle();
                    } else {
                        std::cout << "警告：未定义的标签编号 " << label << "，跳过该目标。" << std::endl;
                    }
                }
                std::cout << "电机动作完成，线程退出。" << std::endl;
            });
            motor_thread.detach();
        }
    }, 500); // 每500ms检查一次

    // 非阻塞主线程轮询
    std::cout << "系统运行中...（主线程非阻塞）" << std::endl;
    while (running) {
        std::this_thread::yield();  // 非阻塞，让出CPU
    }

    // 停止系统
    checkImageTimer.stop();
    cw.stop();
    sorter.stopSystem();
    stopTimerThread();

    std::cout << "系统已安全退出。" << std::endl;
    return 0;
}

