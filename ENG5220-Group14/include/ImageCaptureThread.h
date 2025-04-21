#ifndef IMAGECAPTURETHREAD_H
#define IMAGECAPTURETHREAD_H

#include "CameraCapture.h"
#include <thread>
#include <atomic>
#include <chrono>

class ImageCaptureThread {
public:
    ImageCaptureThread();
    ~ImageCaptureThread();

    void start();
    void stop();

private:
    void run(); // photocycle
    std::thread thread_;
    std::atomic<bool> running_;
    CameraCapture camera_;
};

#endif
