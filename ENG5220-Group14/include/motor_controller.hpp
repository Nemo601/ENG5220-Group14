#include <wiringPi.h>
#include <iostream>
#include <unistd.h>
#include <vector>

using namespace std;

// Step sequence (8 steps)
const int STEPS[8][4] = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}
};

// Four motor pins (BCM numbers)
const vector<vector<int>> MOTOR_PINS = {
    {4, 17, 23, 24},   // Motor 1
    {5, 6, 12, 13},    // Motor 2(You'll need to adjust to the actual connection)
    {16, 20, 21, 26},  // Motor 3
    {18, 19, 22, 27}   // Motor 4
};

// Initialise all motor pins
void initGPIO() {
    wiringPiSetupGpio(); // BCM serial number
    for (const auto& motor : MOTOR_PINS) {
        for (int pin : motor) {
            pinMode(pin, OUTPUT);
            digitalWrite(pin, LOW);
        }
    }
}

// Controls a motor rotation by n steps
void rotateMotor(const vector<int>& pins, int steps = 100, int delayMs = 5) {
    for (int i = 0; i < steps; ++i) {
        int seqIdx = i % 8;
        for (int j = 0; j < 4; ++j) {
            digitalWrite(pins[j], STEPS[seqIdx][j]);
        }
        usleep(delayMs * 1000);
    }
    // Release motor
    for (int pin : pins) {
        digitalWrite(pin, LOW);
    }
}

int main() {
    initGPIO();
    cout << "Start the four motors in sequence...." << endl;

    while (true) {
        for (int i = 0; i < 4; ++i) {
            cout << "electrical machinery " << i+1 << " turn around..." << endl;
            rotateMotor(MOTOR_PINS[i], 100);  // 100 steps per motor rotation
            sleep(1); // Wait 1 second
        }
    }

    return 0;
}
