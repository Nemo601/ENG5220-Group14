#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include <vector>

class StepperMotor {
public:
    StepperMotor(const std::vector<int>& gpioPins);
    void rotate(int steps = 100, bool clockwise = true, int delayMs = 5);
    void release();

private:
    std::vector<int> pins;
    static const int sequence[8][4];
};

#endif
