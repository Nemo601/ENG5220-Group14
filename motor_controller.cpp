#include <wiringPi.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <map>
#include <string>

using namespace std;

// Define the step sequence (8 steps)
const int STEPS[8][4] = {
    {1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0},
    {0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}, {1, 0, 0, 1}
};

// Define Motor Pin (BCM)
const vector<vector<int>> MOTOR_PINS = {
    {4, 17, 23, 24},   // Motor 1
    {5, 6, 12, 13},    // Motor 2
    {16, 20, 21, 26},  // Motor 3
    {18, 19, 22, 27}   // Motor 4
};

// Initialise all pins
void initGPIO() {
    wiringPiSetupGpio();
    for (const auto& motor : MOTOR_PINS) {
        for (int pin : motor) {
            pinMode(pin, OUTPUT);
            digitalWrite(pin, LOW);
        }
    }
}

// Motor Rotation Function
void rotateMotor(const vector<int>& pins, int steps = 100, int delayMs = 5) {
    for (int i = 0; i < steps; ++i) {
        int idx = i % 8;
        for (int j = 0; j < 4; ++j) {
            digitalWrite(pins[j], STEPS[idx][j]);
        }
        usleep(delayMs * 1000);
    }
    for (int pin : pins) {
        digitalWrite(pin, LOW);
    }
}

// Simulation to identify the type of rubbish（back "recyclable", "organic", ...）
string getDetectedType() {
    static int counter = 0;
    vector<string> types = {"recyclable", "organic", "hazardous", "other"};
    string detected = types[counter % types.size()];
    cout << "Spam type identified: " << detected << endl;
    counter++;
    sleep(2);  // Analogue recognition time
    return detected;
}

// Rubbish type to motor mapping
map<string, vector<int>> motorMapping = {
    {"recyclable", {1, 2}},    // Motor 2 和 Motor 3
    {"organic", {0}},          // Motor 1
    {"hazardous", {3}},        // Motor 4
    {"other", {0, 3}}          // Motor 1 和 Motor 4
};

int main() {
    initGPIO();
    cout << "Rubbish Sorting System Launched..." << endl;

    while (true) {
        string type = getDetectedType();

        if (motorMapping.find(type) != motorMapping.end()) {
            for (int motorId : motorMapping[type]) {
                cout << "starter motor " << motorId + 1 << "..." << endl;
                rotateMotor(MOTOR_PINS[motorId], 100);
                usleep(1000 * 500); // 0.5 seconds between motors
            }
        } else {
            cout << "Unknown type, skip processing" << endl;
        }
    }

    return 0;
}
