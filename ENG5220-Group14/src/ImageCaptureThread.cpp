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
            std::cout << "[线程] 拍照成功。\n";
        } else {
            std::cerr << "[线程] 拍照失败。\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}