#include <wiringPi.h>
#include <iostream>
#include <unistd.h> // for usleep

// Defining Pins (BCM Numbering)
#define IN1 4   // BCM 4 => wiringPi 7
#define IN2 17  // BCM 17 => wiringPi 0
#define IN3 23  // BCM 23 => wiringPi 4
#define IN4 24  // BCM 24 => wiringPi 5

void GPIO_init() {
    wiringPiSetupGpio(); // Using BCM Numbers
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
}

void Ground(int Step_Index, int Timer_ms) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

    switch (Step_Index) {
        case 0:
            digitalWrite(IN1, HIGH);
            break;
        case 1:
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, HIGH);
            break;
        case 2:
            digitalWrite(IN2, HIGH);
            break;
        case 3:
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, HIGH);
            break;
        case 4:
            digitalWrite(IN3, HIGH);
            break;
        case 5:
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, HIGH);
            break;
        case 6:
            digitalWrite(IN4, HIGH);
            break;
        case 7:
            digitalWrite(IN1, HIGH);
            digitalWrite(IN4, HIGH);
            break;
    }
    usleep(Timer_ms * 1000);
}

int main() {
    int Step_Index = 0;
    GPIO_init();
    try {
        while (true) {
            Ground(Step_Index, 10); // 10 ms delay
            Step_Index++;
            if (Step_Index == 8) {
                Step_Index = 0;
            }
        }
    } catch (...) {
        std::cerr << "An error occurred" << std::endl;
    }

    // Clear GPIO status (optional)
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

    return 0;
}
