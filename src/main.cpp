int main() {
    Camera cam;
    Classifier classifier("models/model.onnx");
    MotorController motor;
    EventDispatcher dispatcher;

    dispatcher.registerCallback([&motor](const std::string& category) {
        motor.sortTrash(category);
    });

    std::thread capture_thread([&]() {
        while (true) {
            auto frame = cam.captureFrame();
            std::string result = classifier.classify(frame);
            dispatcher.dispatchEvent(result);
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 控制帧率
        }
    });

    capture_thread.join();
    return 0;
}