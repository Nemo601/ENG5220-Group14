class MotorController {
public:
    void sortTrash(const std::string& category); // e.g., rotate servo/motor
private:
    void sendPWM(int angle);
};