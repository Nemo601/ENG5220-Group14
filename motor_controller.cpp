#include <iostream>
#include <string>
#include <wiringPi.h>
#include "StepperMotor.h"
#include "Timer.h"

using namespace std;

int main() {
    wiringPiSetupGpio();

    StepperMotor motor1({4, 17, 23, 24});
    StepperMotor motor2({5, 6, 12, 13});
    StepperMotor motor3({16, 20, 21, 26});
    StepperMotor motor4({18, 19, 22, 27});

    startTimerThread(); // Launching of the timed task system

    string input;
    cout << "Rubbish sorting system has been activated, please enter identification result (1~4 or q)：" << endl;

    while (true) {
        cout << "\nEnter the recognition result (1 to 4 or q)：";
        cin >> input;

        if (input == "q") break;

        if (input == "1") {
            cout << "🔵 Recyclable waste disposal" << endl;
            motor1.rotate(500, true);
            motor2.rotate(500, true);
            scheduleTask(1, [&]() {
                motor1.rotate(500, false);
                motor2.rotate(500, false);
                cout << "🔁 Recyclable withdrawn from completion" << endl;
            });
        }
        else if (input == "2") {
            cout << "🟢 Organic waste disposal" << endl;
            motor2.rotate(1000, true);

            scheduleTask(1, [&]() {
                motor2.rotate(1000, false);
                cout << "🔁 Organic withdrawal completed" << endl;
            });
        }
        else if (input == "3") {
            cout << "🔴 Hazardous waste disposal" << endl;
            motor1.rotate(100, true);

            scheduleTask(1, [&]() {
                motor1.rotate(100, false);
                cout << "🔁 Harmful withdrawals completed" << endl;
            });
        }
        else if (input == "4") {
            cout << "⚫ Other waste disposal" << endl;
            motor4.rotate(100, true);

            scheduleTask(1, [&]() {
                motor4.rotate(100, false);
                cout << "🔁 Other withdrawals completed" << endl;
            });
        }
        else {
            cout << "Invalid input, please re-enter (1~4 or q)" << endl;
        }
    }

    stopTimerThread(); // Stop background threads before program exit
    cout << "The system has exited." << endl;
    return 0;
}
