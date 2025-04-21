#include "ImageCaptureThread.h"
#include <iostream>

ImageCaptureThread::ImageCaptureThread()
    : camera_(), running_(false) {}

ImageCaptureThread::~ImageCaptureThread() {
    stop();
}

void ImageCaptureThread::start() {
    running_ = true;
    thread_ = std::thread(&ImageCaptureThread::run, this);
}

void ImageCaptureThread::stop() {
    running_ = false;
    if (thread_.joinable()) {
        thread_.join();
    }
}

void ImageCaptureThread::run() {
    while (running_) {
        if (camera_.captureImage()) {
            std::cout << "[Thread] Photo taken successfully.\n";
        } else {
            std::cerr << "[Thread] Failed to take a picture.\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}
