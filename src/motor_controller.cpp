#include <iostream>
#include <wiringPi.h>
#include "GarbageSorter.h"
#include "Timer.h"

using namespace std;

int main() {
    wiringPiSetupGpio();
    startTimerThread();
    
    // Initialise motor pinout
    vector<vector<int>> motorPins = {
        {4, 17, 23, 24},  // Motor 1
        {5, 6, 12, 13},    // motor 2
        {16, 20, 21, 26},  // motor 3
        {18, 19, 22, 27}   // motor 4
    };
    
    GarbageSorter sorter(motorPins);
    
    // Setting Status Callbacks
    sorter.setStatusCallback([](const string& msg) {
        cout << "[system status] " << msg << endl;
    });
    
    sorter.startSystem();
    
    string input;
    cout << "The waste sorting system is activated.Please enter the identification result (1~4 or q to exit):" << endl;
    
    while (true) {
        cout << "\nEnter identification result (1-4 or q): ";
        cin >> input;
        
        if (input == "q") {
            break;
        }
        
        try {
            int type = stoi(input);
            if (type >= 1 && type <= 4) {
                sorter.processWaste(static_cast<GarbageSorter::WasteType>(type));
                
                // Wait for the action to complete
                sorter.waitUntilIdle();
            } else {
                cout << "Invalid input, please enter 1-4 or q" << endl;
            }
        } catch (...) {
            cout << "Invalid input, please enter 1-4 or q" << endl;
        }
    }
    
    sorter.stopSystem();
    stopTimerThread();
    cout << "The system has exited." << endl;
    return 0;
}
