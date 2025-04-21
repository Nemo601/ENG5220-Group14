#ifndef THREAD_CONTROLLER_H
#define THREAD_CONTROLLER_H

#include <thread>
#include <atomic>
#include <functional>

class ThreadController {
public:
    using Callback = std::function<void()>;

    ThreadController();
    ~ThreadController();

    void setStartCallback(Callback cb);
    void setStopCallback(Callback cb);

    void startDetection();
    void stopDetection();

    bool isRunning() const;

private:
    std::thread worker_;
    std::atomic<bool> running_;
    Callback start_cb_;
    Callback stop_cb_;
};

#endif
