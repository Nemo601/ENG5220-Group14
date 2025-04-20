#include "CameraCapture.h"

CameraCapture::CameraCapture(int cameraIndex, const std::string& path)
    : savePath(path) {
    cap.open(cameraIndex); // Turn on the camera.
    if (!cap.isOpened()) {
        throw std::runtime_error("Unable to open the camera");
    }
}

CameraCapture::~CameraCapture() {
    cap.release(); // Release the camera.
}

bool CameraCapture::captureImage() {
    cv::Mat frame;
    cap >> frame;
    if (frame.empty()) return false;

    return cv::imwrite(savePath, frame); // overwrite save
}
