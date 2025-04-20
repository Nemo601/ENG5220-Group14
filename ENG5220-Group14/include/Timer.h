#ifndef TIMER_H
#define TIMER_H

#include <functional>

void startTimerThread();
void stopTimerThread();
void scheduleTask(int delaySeconds, std::function<void()> callback);

#endif
