#include "CameraWorker.h"
#include <iostream>

CameraWorker::CameraWorker() : running(false) {}

CameraWorker::~CameraWorker() {
    stop();
}

void CameraWorker::start() {
    running = true;
    workerThread = std::thread(&CameraWorker::run, this);
}

void CameraWorker::stop() {
    running = false;
    if (workerThread.joinable()) {
        workerThread.join();
    }
}

void CameraWorker::run() {
    try {
        CameraCapture camera;
        Timer timer;
        timer.start(2000, [&]() {
            if (camera.captureImage()) {
                std::cout << "Successful photo.\n";
            } else {
                std::cerr << "Failed to take a picture\n";
            }
        });

        while (running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        timer.stop();
    } catch (const std::exception& e) {
        std::cerr << "Camera Thread Exception: " << e.what() << std::endl;
    }
}
