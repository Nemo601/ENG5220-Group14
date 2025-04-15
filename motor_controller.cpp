#include <wiringPi.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <unistd.h>
#include "StepperMotor.h"

using namespace std;

string getDetectedType() {
    static int i = 0;
    vector<string> types = {"recyclable", "organic", "hazardous", "other"};
    string type = types[i % types.size()];
    i++;
    sleep(2); // Analogue recognition delay
    return type;
}

int main() {
    wiringPiSetupGpio();  // Using BCM Pin Numbering

    // Instantiate four motors
    StepperMotor motor1({4, 17, 23, 24});
    StepperMotor motor2({5, 6, 12, 13});
    StepperMotor motor3({16, 20, 21, 26});
    StepperMotor motor4({18, 19, 22, 27});

    // The rubbish type corresponds to the motor to be rotated
    map<string, vector<StepperMotor*>> motorMap = {
        {"recyclable", {&motor2, &motor3}},
        {"organic", {&motor1}},
        {"hazardous", {&motor4}},
        {"other", {&motor1, &motor4}}
    };

    cout << "Launch of Intelligent Waste Separation System..." << endl;

    while (true) {
        string type = getDetectedType();
        cout << "Identify to type：" << type << endl;

        if (motorMap.count(type)) {
            for (auto motor : motorMap[type]) {
                motor->rotate(100);
                usleep(500 * 1000);
            }
        } else {
            cout << "Unknown type, skip processing." << endl;
        }
    }

    return 0;
}
