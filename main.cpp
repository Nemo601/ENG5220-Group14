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
const std::string watch_path = "/home/pi/images";
bool image_exists = false;

void signalHandler(int) {
    running = false;
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
    // 垃圾编号 -> 分类映射（编号是YOLO检测label，分类是电机控制所需）
    std::unordered_map<int, int> label_to_category = {
        {0, 1}, {1, 2}, {2, 3}, {3, 2}, {4, 1}
        // 按照“标签编号及垃圾分类.xlsx”配置更多项
    };

    wiringPiSetupGpio();
    const int SENSOR_PIN = 00;
    pinMode(SENSOR_PIN, INPUT);
    pullUpDnControl(SENSOR_PIN, PUD_UP);
    signal(SIGINT, signalHandler);

    std::cout << "等待光电传感器触发..." << std::endl;
    while (digitalRead(SENSOR_PIN) == HIGH && running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "物体检测到，系统启动！" << std::endl;

    CameraWorker cw;
    cw.start();
    startTimerThread();
    signal(SIGINT, signalHandler);

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

    while (running) {
        bool now_has_image = hasImageInDirectory(watch_path);

        if (now_has_image && !image_exists) {
            std::cout << "[事件] 检测到图片出现，启动识别线程。" << std::endl;

            std::thread detect_thread([&detector]() {
                for (const auto& entry : fs::directory_iterator(watch_path)) {
                    if (entry.is_regular_file()) {
                        std::string ext = entry.path().extension().string();
                        if (ext == ".jpg" || ext == ".png" || ext == ".jpeg" || ext == ".bmp") {
                            cv::Mat img = cv::imread(entry.path().string());
                            if (!img.empty()) {
                                detector.detect(img);
                                break;
                            }
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
                latest_result.reset();
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

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    cw.stop();
    sorter.stopSystem();
    stopTimerThread();
    std::cout << "系统已退出。" << std::endl;
    return 0;
}
