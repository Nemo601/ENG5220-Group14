#include "Timer.h"
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
atomic<bool> running(false);

void timerLoop() {
    while (running) {
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
    running = true;
    thread(timerLoop).detach(); // Starting background threads
}

void stopTimerThread() {
    running = false;
    cv.notify_all();
}

void scheduleTask(int delaySeconds, function<void()> callback) {
    lock_guard<mutex> lock(queueMutex);
    taskQueue.push({steady_clock::now() + seconds(delaySeconds), callback});
    cv.notify_one();
}
