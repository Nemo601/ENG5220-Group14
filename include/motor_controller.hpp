#include <wiringPi.h>
#include <iostream>
#include <unistd.h>
#include <vector>

using namespace std;

// 步进序列（8步）
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

// 四个电机的引脚（BCM编号）
const vector<vector<int>> MOTOR_PINS = {
    {4, 17, 23, 24},   // Motor 1
    {5, 6, 12, 13},    // Motor 2（你需要按实际连线调整）
    {16, 20, 21, 26},  // Motor 3
    {18, 19, 22, 27}   // Motor 4
};

// 初始化所有电机引脚
void initGPIO() {
    wiringPiSetupGpio(); // BCM 编号
    for (const auto& motor : MOTOR_PINS) {
        for (int pin : motor) {
            pinMode(pin, OUTPUT);
            digitalWrite(pin, LOW);
        }
    }
}

// 控制某一个电机旋转 n 步
void rotateMotor(const vector<int>& pins, int steps = 100, int delayMs = 5) {
    for (int i = 0; i < steps; ++i) {
        int seqIdx = i % 8;
        for (int j = 0; j < 4; ++j) {
            digitalWrite(pins[j], STEPS[seqIdx][j]);
        }
        usleep(delayMs * 1000);
    }
    // 释放电机
    for (int pin : pins) {
        digitalWrite(pin, LOW);
    }
}

int main() {
    initGPIO();
    cout << "开始四个电机依次运转..." << endl;

    while (true) {
        for (int i = 0; i < 4; ++i) {
            cout << "电机 " << i+1 << " 运转..." << endl;
            rotateMotor(MOTOR_PINS[i], 100);  // 每个电机转动 100 步
            sleep(1); // 等待 1 秒
        }
    }

    return 0;
}
