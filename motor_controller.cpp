#include <wiringPi.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include "StepperMotor.h"

using namespace std;

void performAction(const string& type,
                   StepperMotor& m1, StepperMotor& m2,
                   StepperMotor& m3, StepperMotor& m4) {
    if (type == "recyclable") {
        // Motor 2, 3 100 steps clockwise
        m2.rotate(100, true);
        m3.rotate(100, true);
        // Motor 4 1000 steps clockwise
        m4.rotate(1000, true);
        sleep(5);
        // Motor 2, 3 100 steps counterclockwise
        m2.rotate(100, false);
        m3.rotate(100, false);
        // Motor 4 1000 steps counterclockwise
        m4.rotate(1000, false);
    } else if (type == "organic") {
        // Motor 2 100 steps clockwise
        m2.rotate(100, true);
        sleep(5);
        // Motor 2 100 steps counterclockwise
        m2.rotate(100, false);
    } else if (type == "hazardous") {
        // Motor 1 100 steps clockwise
        m1.rotate(100, true);
        sleep(5);
        // Motor 1 100 steps counterclockwise
        m1.rotate(100, false);
    } else if (type == "other") {
        // Motor 3 100 steps clockwise
        m3.rotate(100, true);
        sleep(5);
        // Motor 3 100 steps counterclockwise
        m3.rotate(100, false);
    } else {
        cout << "❌ Invalid type。" << endl;
    }
}

int main() {
    wiringPiSetupGpio();  // Using BCM Numbers

    StepperMotor motor1({4, 17, 23, 24});
    StepperMotor motor2({5, 6, 12, 13});
    StepperMotor motor3({16, 20, 21, 26});
    StepperMotor motor4({18, 19, 22, 27});

    cout << "🗑️ Launch of Intelligent Waste Separation System..." << endl;
    cout << "keypad control：" << endl;
    cout << "  r - recyclable" << endl;
    cout << "  o - organic" << endl;
    cout << "  h - hazardous" << endl;
    cout << "  t - other" << endl;
    cout << "  q - quit" << endl;

    while (true) {
        cout << "\nInput rubbish type (r/o/h/t/q): ";
        char input;
        cin >> input;

        string type;

        switch (input) {
            case 'r': type = "recyclable"; break;
            case 'o': type = "organic"; break;
            case 'h': type = "hazardous"; break;
            case 't': type = "other"; break;
            case 'q':
                cout << "👋 quit！" << endl;
                return 0;
            default:
                cout << "⚠️ Invalid input, please try again." << endl;
                continue;
        }

        cout << "Identify to type：" << type << "，start..." << endl;
        performAction(type, motor1, motor2, motor3, motor4);
    }

    return 0;
}
