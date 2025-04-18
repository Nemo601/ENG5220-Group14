#ifndef YOLO_DETECT_H
#define YOLO_DETECT_H

#include <opencv2/core.hpp>
#include <vector>
#include <functional>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>

struct Object {
    cv::Rect_<float> rect;
    int label;
    float prob;
};

// 异步回调代码
struct PrioritizedCallback {
    int priority;  // 优先级数字越小，优先级越高
    DetectionCallback callback;
    bool operator<(const PrioritizedCallback& other) const {
        return priority > other.priority;  // 小顶堆
    }
};

class YoloDetector {
public:
    using DetectionCallback = std::function<void(const std::vector<Object>&)>;

    // 链式回调代码
    using ChainedCallback = std::function<std::vector<Object>(const std::vector<Object>&)>;

    YoloDetector();
    ~YoloDetector();

    bool loadModel(const std::string& param_path, const std::string& bin_path);
    int detect(const cv::Mat& image);

    void setCallback(DetectionCallback callback);

    // 异步用法
    void enqueueFrame(const cv::Mat& image); // 新增：输入图像队列
    void start();                            // 新增：启动线程
    void stop();                             // 新增：停止线程

private:
    class Impl;
    Impl* impl_;
};

#endif // YOLO_DETECT_H