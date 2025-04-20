#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <opencv2/opencv.hpp>

struct SharedData {
    // 摄像头到YOLO的帧队列
    std::queue<cv::Mat> frame_queue;
    std::mutex frame_mutex;
    std::condition_variable frame_cv;
    
    // YOLO到电机的检测结果
    struct DetectionResult {
        // 根据你的检测结果定义
        int object_id;
        float confidence;
        cv::Rect bounding_box;
    };
    
    std::queue<DetectionResult> motor_queue;
    std::mutex motor_mutex;
    std::condition_variable motor_cv;
    
    // 系统控制标志
    bool system_running = true;
};

#endif // SHARED_DATA_H