#include "./include/yolo_detect.h"
#include "./include/ImageCaptureThread.h"
#include "./include/CameraCapture"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

void draw_objects(const cv::Mat& image, const std::vector<Object>& objects) {
    static const char* class_names[] = {
        "person", "bicycle", "car", "motorcycle", "airplane", "bus"
        // 可根据 COCO 数据集继续扩展
    };

    cv::Mat vis = image.clone();
    for (const auto& obj : objects) {
        cv::rectangle(vis, obj.rect, cv::Scalar(0, 255, 0), 2);
        char label[100];
        sprintf(label, "%s %.1f%%", class_names[obj.label], obj.prob * 100);
        cv::putText(vis, label, obj.rect.tl(), cv::FONT_HERSHEY_SIMPLEX, 0.5, {0, 0, 255}, 1);
    }

    cv::imshow("YOLOv5 Detection", vis);
    // 等待（要删除）
    cv::waitKey(0);
}

int main(int argc, char** argv) {
    ImageCaptureThread captureThread;
    captureThread.start();
    if (argc != 2) {
        std::cerr << "Usage: ./yolo_detect [image_path]\n";
        return -1;
    }

    cv::Mat image = cv::imread(argv[1]);
    if (image.empty()) {
        std::cerr << "Failed to read image: " << argv[1] << "\n";
        return -1;
    }

    YoloDetector detector;
    detector.setCallback([&image](const std::vector<Object>& objects) {
        draw_objects(image, objects);
    });

    if (!detector.loadModel("v5lite-e.param", "v5lite-e.bin")) {
        std::cerr << "Model load failed.\n";
        return -1;
    }

    detector.detect(image);
    return 0;
}