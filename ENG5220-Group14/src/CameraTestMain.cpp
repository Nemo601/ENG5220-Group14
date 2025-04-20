#include "CameraWorker.h"
#include <iostream>

int main() {
    CameraWorker camThread;
    camThread.start(); 

    std::cout << "The main program is running and logic such as image recognition can be executed here.\n";
    std::cout << "Press enter to exit..." << std::endl;
    std::cin.get();

    camThread.stop(); 
    return 0;
}
