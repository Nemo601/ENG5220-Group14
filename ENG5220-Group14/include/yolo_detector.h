
#ifndef YOLO_DETECTOR_H
#define YOLO_DETECTOR_H

#include <opencv2/core.hpp>
#include <vector>
#include <functional>

struct Object {
    cv::Rect_<float> rect;
    int label;
    float prob;
};

class YoloDetector {
public:
    using DetectionCallback = std::function<void(const std::vector<Object>&)>;

    YoloDetector();
    ~YoloDetector();

    bool loadModel(const std::string& param_path, const std::string& bin_path);
    int detect(const cv::Mat& image);
    void setCallback(DetectionCallback callback);

private:
    class Impl;
    Impl* impl_;
};

#endif // YOLO_DETECTOR_H
