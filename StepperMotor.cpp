#include "StepperMotor.h"

StepperMotor::StepperMotor(const std::vector<int>& pins) : _pins(pins) {
    for (int pin : _pins) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }
}

void StepperMotor::step(int steps, bool clockwise, int speedMs) {
    for (int i = 0; i < steps; i++) {
        int idx = clockwise ? i % 8 : (7 - (i % 8));
        for (int j = 0; j < 4; j++) {
            digitalWrite(_pins[j], _sequence[idx][j]);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(speedMs));
    }
    release();
}

void StepperMotor::release() {
    for (int pin : _pins) {
        digitalWrite(pin, LOW);
    }
}
