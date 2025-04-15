class Camera {
public:
    Camera();
    ~Camera();
    cv::Mat captureFrame(); // 封装OpenCV
private:
    cv::VideoCapture cap;
};