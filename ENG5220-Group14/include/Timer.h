#ifndef TIMER_H
#define TIMER_H

#include <functional>
#include <chrono>
#include <atomic>

class IntervalTimer {
public:
    void setInterval(std::function<void()> func, int interval_ms);
    void stop();

private:
    std::atomic<bool> active{true};
};

void startTimerThread();
void stopTimerThread();
void scheduleTask(int delaySeconds, std::function<void()> callback);

#endif
