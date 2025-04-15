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
    cout << "Press the following keys to simulate the input of a rubbish type：" << endl;
    cout << "r - recyclable  o - organic  h - hazardous  t - other  q - quit" << endl;

   
