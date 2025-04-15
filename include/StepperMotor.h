#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include <wiringPi.h>
#include <vector>
#include <thread>
#include <chrono>

class StepperMotor {
public:
    StepperMotor(const std::vector<int>& pins);
    void step(int steps, bool clockwise = true, int speedMs = 2);
    void release();

private:
    std::vector<int> _pins;
    const int _sequence[8][4] = {
        {1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,1,1,0},
        {0,0,1,0}, {0,0,1,1}, {0,0,0,1}, {1,0,0,1}
    };
};

#endif