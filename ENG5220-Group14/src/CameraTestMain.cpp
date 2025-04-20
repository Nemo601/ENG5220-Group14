#include <iostream>
#include "CameraCapture.h"
#include "CameraTimer.h"

int main() {
    try {
        CameraCapture camera; 
        Timer timer;

        timer.start(2000, [&]() {
            if (camera.captureImage()) {
                std::cout << "Saved images.\n";
            } else {
                std::cerr << "Failed to take a picture.\n";
            }
        });

        std::cout << "The image is saved every two seconds while the programme is running.\n Press enter to exit..." << std::endl;
        std::cin.get();

        timer.stop();
    } catch (const std::exception& ex) {
        std::cerr << "Procedure error:" << ex.what() << std::endl;
    }

    return 0;
}
