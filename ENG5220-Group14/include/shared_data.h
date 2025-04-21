#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <opencv2/opencv.hpp>

struct SharedData {
    // Camera to YOLO frame queue
    std::queue<cv::Mat> frame_queue;
    std::mutex frame_mutex;
    std::condition_variable frame_cv;
    
    // YOLO to motor test results
    struct DetectionResult {
        // Defined by your test results
        int object_id;
        float confidence;
        cv::Rect bounding_box;
    };
    
    std::queue<DetectionResult> motor_queue;
    std::mutex motor_mutex;
    std::condition_variable motor_cv;
    
    // System Control Flag
    bool system_running = true;
};

#endif // SHARED_DATA_H
