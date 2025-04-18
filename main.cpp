#include "yolo_detect.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <atomic>
#include <csignal>

std::atomic<bool> running(true);

// 可视化检测结果
void draw_objects(const cv::Mat& image, const std::vector<Object>& objects) {
    static const char* class_names[] = {
        "person", "bicycle", "car", "motorcycle", "airplane", "bus"
    };

    cv::Mat vis = image.clone();
    for (const auto& obj : objects) {
        cv::rectangle(vis, obj.rect, cv::Scalar(0, 255, 0), 2);
        char label[100];
        sprintf(label, "%s %.1f%%", class_names[obj.label], obj.prob * 100);
        cv::putText(vis, label, obj.rect.tl(), cv::FONT_HERSHEY_SIMPLEX, 0.5, {0, 0, 255}, 1);
    }

    cv::imshow("YOLOv5 Detection", vis);
    cv::waitKey(1);  // 注意：不再是 waitKey(0)
}

void signalHandler(int) {
    running = false;
}

int main() {
    signal(SIGINT, signalHandler);  // 支持 Ctrl+C 退出

    // 初始化摄像头
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Failed to open camera\n";
        return -1;
    }

    // 初始化检测器
    YoloDetector detector;
    if (!detector.loadModel("v5lite-e.param", "v5lite-e.bin")) {
        std::cerr << "Model load failed.\n";
        return -1;
    }

    detector.setCallback([](const std::vector<Object>& objects) {
        if (!objects.empty()) {
            std::cout << "Detected " << objects.size() << " object(s).\n";
        }
        // 注意：draw_objects 只能显示“当前帧”，如果你要展示帧内容，应将图像一并传递进回调
        // 为简化，此处不显示图像；真实项目建议共享图像队列用于同步可视化
    });

    detector.start();

    // 主循环：不断采图 → 入队检测
    while (running) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) continue;

        detector.enqueueFrame(frame);  // 入队
        std::this_thread::sleep_for(std::chrono::milliseconds(30));  // 控帧率
    }

    detector.stop();
    return 0;
}
