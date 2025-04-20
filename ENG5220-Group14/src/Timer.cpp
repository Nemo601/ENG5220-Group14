#include "../include/Timer.h"
#include <queue>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

using namespace std;
using namespace std::chrono;

struct TimerTask {
    time_point<steady_clock> executeTime;
    function<void()> callback;
};

queue<TimerTask> taskQueue;
mutex queueMutex;
condition_variable cv;
atomic<bool> runnings(false);

void timerLoop() {
    while (runnings) {
        unique_lock<mutex> lock(queueMutex);
        if (!taskQueue.empty()) {
            auto now = steady_clock::now();
            auto& task = taskQueue.front();
            if (now >= task.executeTime) {
                auto callback = task.callback;
                taskQueue.pop();
                lock.unlock();
                callback();
            } else {
                cv.wait_until(lock, task.executeTime);
            }
        } else {
            cv.wait(lock);
        }
    }
}

void startTimerThread() {
    runnings = true;
    thread(timerLoop).detach(); // Starting background threads
}

void stopTimerThread() {
    runnings = false;
    cv.notify_all();
}

void scheduleTask(int delaySeconds, function<void()> callback) {
    lock_guard<mutex> lock(queueMutex);
    taskQueue.push({steady_clock::now() + seconds(delaySeconds), callback});
    cv.notify_one();
}

void IntervalTimer::setInterval(std::function<void()> func, int interval_ms) {
    active = true;
    thread([=]() {
        while (active.load()) {
            auto start = steady_clock::now();
            func();
            auto end = steady_clock::now();
            auto elapsed = duration_cast<milliseconds>(end - start);
            auto sleep_time = milliseconds(interval_ms) - elapsed;
            if (sleep_time.count() > 0) {
                this_thread::sleep_for(sleep_time);
            }
        }
    }).detach();
}

void IntervalTimer::stop() {
    active = false;
}
