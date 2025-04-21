#include "ThreadController.h"

ThreadController::ThreadController() : running_(false) {}

ThreadController::~ThreadController() {
    stopDetection();
}

void ThreadController::setStartCallback(Callback cb) {
    start_cb_ = cb;
}

void ThreadController::setStopCallback(Callback cb) {
    stop_cb_ = cb;
}

void ThreadController::startDetection() {
    if (running_) return;
    running_ = true;

    worker_ = std::thread([this]() {
        if (start_cb_) start_cb_();
    });
}

void ThreadController::stopDetection() {
    if (!running_) return;
    running_ = false;
    if (worker_.joinable()) worker_.join();
    if (stop_cb_) stop_cb_();
}

bool ThreadController::isRunning() const {
    return running_;
}
