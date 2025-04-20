#pragma once
#include <ncnn/net.h>
#include <opencv2/opencv.hpp>
#include <vector>

struct Detection {
    cv::Rect box;
    float score;
    int label;
};

class NCNNDetector {
public:
    NCNNDetector(const std::string& param, const std::string& bin);
    std::vector<Detection> detect(const cv::Mat& image, float score_threshold = 0.5f);
private:
    ncnn::Net net;
    int input_width = 320;
    int input_height = 320;
};