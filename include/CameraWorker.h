#ifndef CAMERAWORKER_H
#define CAMERAWORKER_H

#include "CameraCapture.h"
#include "CameraTimer.h"
#include <thread>
#include <atomic>

class CameraWorker {
public:
    CameraWorker();
    ~CameraWorker();

    void start();   // Start the photo thread
    void stop();    // Stop the photo thread

private:
    void run(); // subthread function

    std::atomic<bool> running;
    std::thread workerThread;
};

#endif
