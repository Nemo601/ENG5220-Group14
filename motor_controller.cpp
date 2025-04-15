#include <wiringPi.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <unistd.h>
#include "StepperMotor.h"

using namespace std;

int main() {
    wiringPiSetupGpio();  // Using BCM Numbers

    // Instantiating four stepper motors
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

    cout << "🗑️ Launch of Intelligent Waste Separation System..." << endl;
    cout << "Press the following buttons to simulate the input rubbish type：" << endl;
    cout << "  r -  recyclable" << endl;
    cout << "  o -  organic" << endl;
    cout << "  h -  hazardous" << endl;
    cout << "  t -  other" << endl;
    cout << "  q - quit" << endl;

    while (true) {
        cout << "\nPlease enter the type (r/o/h/t/q): ";
        char input;
        cin >> input;

        string type;

        switch (input) {
            case 'r': type = "recyclable"; break;
            case 'o': type = "organic"; break;
            case 'h': type = "hazardous"; break;
            case 't': type = "other"; break;
            case 'q': 
                cout << "quit" << endl;
                return 0;
            default:
                cout << "⚠️ Invalid input, please re-enter." << endl;
                continue;
        }

        cout << "Identify to type：" << type << "，Processing..." << endl;

        if (motorMap.count(type)) {
            for (auto motor : motorMap[type]) {
                motor->rotate(100);
                usleep(500 * 1000);  // 500ms 延迟
            }
        } else {
            cout << "⚠️ Unknown type, skip processing." << endl;
        }
    }

    return 0;
}
