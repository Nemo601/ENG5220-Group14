#ifndef TIMER_H
#define TIMER_H

#include <functional>
#include <thread>
#include <atomic>
#include <chrono>

class Timer {
public:
    Timer();
    ~Timer();

    void start(int intervalMs, std::function<void()> task);
    void stop();

private:
    std::atomic<bool> running;
    std::thread worker;
};

#endif
