#include "StepperMotor.h"
#include <wiringPi.h>
#include <unistd.h>

const int StepperMotor::sequence[8][4] = {
    {1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0},
    {0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}, {1, 0, 0, 1}
};

StepperMotor::StepperMotor(const std::vector<int>& gpioPins) : pins(gpioPins) {
    for (int pin : pins) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }
}

void StepperMotor::rotate(int steps, bool clockwise, int delayMs) {
    for (int i = 0; i < steps; ++i) {
        int idx = clockwise ? i % 8 : 7 - (i % 8);
        for (int j = 0; j < 4; ++j) {
            digitalWrite(pins[j], sequence[idx][j]);
        }
        usleep(delayMs * 1000);
    }
    release();
}

void StepperMotor::release() {
    for (int pin : pins) {
        digitalWrite(pin, LOW);
    }
}
