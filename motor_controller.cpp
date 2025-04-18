#include <iostream>
#include <string>
#include <atomic>
#include <thread>
#include <chrono>
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

    startTimerThread(); // Starting a timed task thread

    atomic<bool> isBusy(false);
    string input;

    cout << " Rubbish sorting system activated. Please enter recognition result (1~4 or q):" << endl;

    while (true) {
        // Wait for the current task to complete before allowing input
        while (isBusy.load()) {
            this_thread::sleep_for(chrono::milliseconds(100));
        }

        cout << "\nEnter the recognition result (1 to 4 or q): ";
        cin >> input;

        if (input == "q") break;

        isBusy.store(true); // Setting Busy Status

        if (input == "1") {
            cout << " Recyclable waste disposal" << endl;
            motor1.rotate(500, true);
            motor2.rotate(500, true);

            scheduleTask(1, [&]() {
                motor1.rotate(500, false);
                motor2.rotate(500, false);
                cout << " Recyclable withdrawal completed" << endl;
                isBusy.store(false);
            });
        }
        else if (input == "2") {
            cout << " Organic waste disposal" << endl;
            motor2.rotate(1000, true);

            scheduleTask(1, [&]() {
                motor2.rotate(1000, false);
                cout << " Organic withdrawal completed" << endl;
                isBusy.store(false);
            });
        }
        else if (input == "3") {
            cout << " Hazardous waste disposal" << endl;
            motor1.rotate(100, true);

            scheduleTask(1, [&]() {
                motor1.rotate(100, false);
                cout << "Hazardous withdrawal completed" << endl;
                isBusy.store(false);
            });
        }
        else if (input == "4") {
            cout << " Other waste disposal" << endl;
            motor4.rotate(100, true);

            scheduleTask(1, [&]() {
                motor4.rotate(100, false);
                cout << " Other withdrawal completed" << endl;
                isBusy.store(false);
            });
        }
        else {
            cout << " Invalid input. Please enter 1 to 4 or q." << endl;
            isBusy.store(false);
        }
    }

    stopTimerThread(); // Stopping the timer thread
    cout << " System exited." << endl;
    return 0;
}
