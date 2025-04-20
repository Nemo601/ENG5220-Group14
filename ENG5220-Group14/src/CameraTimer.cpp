#include "CameraTimer.h"

Timer::Timer() : running(false) {}

Timer::~Timer() {
    stop();
}

void Timer::start(int intervalMs, std::function<void()> task) {
    running = true;
    worker = std::thread([=]() {
        while (running) {
            auto start = std::chrono::steady_clock::now();
            task(); // operate
            std::this_thread::sleep_until(start + std::chrono::milliseconds(intervalMs));
        }
    });
}

void Timer::stop() {
    running = false;
    if (worker.joinable()) {
        worker.join(); // Waiting for the thread to exit
    }
}
