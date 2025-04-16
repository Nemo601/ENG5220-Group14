#ifndef CAMERACAPTURE_H
#define CAMERACAPTURE_H

#include <opencv2/opencv.hpp>
#include <string>

class CameraCapture {
public:
    CameraCapture(int cameraIndex = 0, const std::string& path = ""/home/pi/project/cpp_demo/picture/captured.jpg"");
    ~CameraCapture();

    bool captureImage(); // Save directly to the specified path

private:
    cv::VideoCapture cap;
    std::string savePath; // Storage path
};

#endif
