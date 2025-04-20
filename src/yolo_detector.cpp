#include "yolo_detect.h"
#include "net.h"
#include <cmath>
#include <float.h>
#include <algorithm>

class YoloDetector::Impl {
public:
    Impl();
    ~Impl();

    bool loadModel(const std::string& param_path, const std::string& bin_path);
    int detect(const cv::Mat& image);
    void setCallback(DetectionCallback cb);

    // 异步用法
    void enqueueFrame(const cv::Mat& image); // 新增：输入图像队列
    void start();                            // 新增：启动线程
    void stop();                             // 新增：停止线程

private:
    void generateProposals(const ncnn::Mat& anchors, int stride, const ncnn::Mat& in_pad,
                           const ncnn::Mat& feat_blob, float prob_threshold,
                           std::vector<Object>& proposals);

    float sigmoid(float x);
    float unsigmoid(float y);
    float intersectionArea(const Object& a, const Object& b);
    void sortDescending(std::vector<Object>& objs);
    void nms(const std::vector<Object>& proposals, std::vector<int>& picked, float nms_threshold);

    void detectLoop();                         // 新增：工作线程函数
    int detect(const cv::Mat& image);          // 保留已有检测函数

private:
    ncnn::Net yolov5_;
    DetectionCallback callback_;

    // 异步回调代码
    // std::priority_queue<PrioritizedCallback> callbacks_;
    // 链式回调代码
    // std::vector<ChainedCallback> callbacks_;
};

YoloDetector::Impl::Impl() {
#if USE_INT8
    yolov5_.opt.use_int8_inference = true;
#else
    yolov5_.opt.use_vulkan_compute = true;
    yolov5_.opt.use_bf16_storage = true;
#endif
}

YoloDetector::Impl::~Impl() {}

bool YoloDetector::Impl::loadModel(const std::string& param_path, const std::string& bin_path) {
    return yolov5_.load_param(param_path.c_str()) == 0 && yolov5_.load_model(bin_path.c_str()) == 0;
}

// 异步回调代码
// void addCallback(int priority, DetectionCallback cb) {
       // 加锁操作    
//     std::lock_guard<std::mutex> lock(mtx_);
//     callbacks_.push({priority, cb});
// }

// 链式回调代码
// void addCallback(ChainedCallback cb) {
//     callbacks_.push_back(cb);
// }


float YoloDetector::Impl::sigmoid(float x) { return 1.f / (1.f + exp(-x)); }
float YoloDetector::Impl::unsigmoid(float y) { return -1.0f * log((1.0f / y) - 1.0f); }

float YoloDetector::Impl::intersectionArea(const Object& a, const Object& b) {
    return (a.rect & b.rect).area();
}


// 不理解功能
void YoloDetector::Impl::sortDescending(std::vector<Object>& objs) {
    std::sort(objs.begin(), objs.end(), [](const Object& a, const Object& b) {
        return a.prob > b.prob;
    });
}


// 不理解功能
void YoloDetector::Impl::nms(const std::vector<Object>& proposals, std::vector<int>& picked, float nms_threshold) {
    picked.clear();
    const int n = proposals.size();
    std::vector<float> areas(n);
    for (int i = 0; i < n; ++i) areas[i] = proposals[i].rect.area();

    for (int i = 0; i < n; ++i) {
        const Object& a = proposals[i];
        bool keep = true;
        for (int j : picked) {
            const Object& b = proposals[j];
            float inter_area = intersectionArea(a, b);
            float union_area = areas[i] + areas[j] - inter_area;
            if (inter_area / union_area > nms_threshold) {
                keep = false;
                break;
            }
        }
        if (keep) picked.push_back(i);
    }
}

void YoloDetector::Impl::generateProposals(const ncnn::Mat& anchors, int stride, const ncnn::Mat& in_pad,
                                           const ncnn::Mat& feat_blob, float prob_threshold,
                                           std::vector<Object>& proposals) {
    const int num_grid = feat_blob.h;
    const int num_class = feat_blob.w - 5;
    const int num_anchors = anchors.w / 2;
    int num_grid_x = in_pad.w / stride;
    int num_grid_y = in_pad.h / stride;

    for (int q = 0; q < num_anchors; q++) {
        float anchor_w = anchors[q * 2];
        float anchor_h = anchors[q * 2 + 1];
        const ncnn::Mat feat = feat_blob.channel(q);
        // for 循环看不懂，大受震撼
        for (int i = 0; i < num_grid_y; i++) {
            for (int j = 0; j < num_grid_x; j++) {
                const float* featptr = feat.row(i * num_grid_x + j);
                // find class index with max class score
                float box_score = featptr[4];
                if (sigmoid(box_score) < prob_threshold) continue;

                float class_score = -FLT_MAX;
                int class_index = -1;
                for (int k = 0; k < num_class; k++) {
                    float score = featptr[5 + k];
                    if (score > class_score) {
                        class_score = score;
                        class_index = k;
                    }
                }

                float confidence = sigmoid(box_score) * sigmoid(class_score);
                if (confidence < prob_threshold) continue;

                float dx = sigmoid(featptr[0]);
                float dy = sigmoid(featptr[1]);
                float dw = sigmoid(featptr[2]);
                float dh = sigmoid(featptr[3]);

                float pb_cx = (dx * 2.f - 0.5f + j) * stride;
                float pb_cy = (dy * 2.f - 0.5f + i) * stride;
                float pb_w = pow(dw * 2.f, 2.f) * anchor_w;
                float pb_h = pow(dh * 2.f, 2.f) * anchor_h;

                float x0 = pb_cx - pb_w * 0.5f;
                float y0 = pb_cy - pb_h * 0.5f;

                Object obj;
                obj.rect = cv::Rect_<float>(x0, y0, pb_w, pb_h);
                obj.label = class_index;
                obj.prob = confidence;

                proposals.push_back(obj);
            }
        }
    }
}

int YoloDetector::Impl::detect(const cv::Mat& bgr) {
    std::vector<Object> objects;
    int img_w = bgr.cols, img_h = bgr.rows;
    int target_size = 320;
    float scale = (float)target_size / std::max(img_w, img_h);
    int new_w = img_w * scale, new_h = img_h * scale;

    ncnn::Mat in = ncnn::Mat::from_pixels_resize(bgr.data, ncnn::Mat::PIXEL_BGR2RGB, img_w, img_h, new_w, new_h);
    int wpad = (new_w + 31) / 32 * 32 - new_w;
    int hpad = (new_h + 31) / 32 * 32 - new_h;

    ncnn::Mat in_pad;
    ncnn::copy_make_border(in, in_pad, hpad/2, hpad-hpad/2, wpad/2, wpad-wpad/2, ncnn::BORDER_CONSTANT, 114.f);

    const float norm_vals[3] = {1/255.f, 1/255.f, 1/255.f};
    in_pad.substract_mean_normalize(0, norm_vals);

    ncnn::Extractor ex = yolov5_.create_extractor();
    ex.input("images", in_pad);

    std::vector<std::pair<std::string, std::vector<float>>> layers = {
        {"output", {10,13, 16,30, 33,23}},
        {"1111",   {30,61, 62,45, 59,119}},
        {"2222",   {116,90, 156,198, 373,326}}
    };

    std::vector<Object> proposals;
    for (size_t i = 0; i < layers.size(); ++i) {
        ncnn::Mat out;
        ex.extract(layers[i].first.c_str(), out);
        ncnn::Mat anchors((int)layers[i].second.size());
        for (size_t j = 0; j < layers[i].second.size(); ++j)
            anchors[j] = layers[i].second[j];
        generateProposals(anchors, (1 << (i + 3)), in_pad, out, 0.6f, proposals);
    }

    sortDescending(proposals);
    std::vector<int> picked;
    nms(proposals, picked, 0.6f);

    objects.resize(picked.size());
    for (size_t i = 0; i < picked.size(); ++i) {
        Object& obj = proposals[picked[i]];
        float x0 = (obj.rect.x - wpad/2) / scale;
        float y0 = (obj.rect.y - hpad/2) / scale;
        float x1 = (obj.rect.x + obj.rect.width - wpad/2) / scale;
        float y1 = (obj.rect.y + obj.rect.height - hpad/2) / scale;

        x0 = std::clamp(x0, 0.f, (float)(img_w - 1));
        y0 = std::clamp(y0, 0.f, (float)(img_h - 1));
        x1 = std::clamp(x1, 0.f, (float)(img_w - 1));
        y1 = std::clamp(y1, 0.f, (float)(img_h - 1));

        objects[i] = {cv::Rect_<float>(x0, y0, x1 - x0, y1 - y0), obj.label, obj.prob};
    }
    // ... 执行检测，填充objects，object是触发回调的条件
    if (callback_) callback_(objects);     // 检查回调是否有效，并触发回调，传递检测结果



    // 带加锁操作的复制原队列操作
    // std::priority_queue<PrioritizedCallback> tmp;
    //     {
    //         std::lock_guard<std::mutex> lock(mtx_);
    //         tmp = callbacks_;  // 加锁复制
    //     }
    // 异步回调代码
    // auto tmp = callbacks_;  // 复制以避免修改原队列
    //     while (!tmp.empty()) {
    //         tmp.top().callback(objects);  // 按优先级从高到低触发
    //         tmp.pop();


    // 链式回调代码
    // for (const auto& cb : callbacks_) {
    //     objects = cb(objects);  // 链式传递数据
    // }



    return 0;
}

void YoloDetector::Impl::setCallback(DetectionCallback cb) {
    callback_ = cb;
}


// 新增代码
void YoloDetector::Impl::enqueueFrame(const cv::Mat& image) {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        frame_queue_.push(image.clone());  // 克隆确保数据完整
    }
    cv_.notify_one();
}

void YoloDetector::Impl::detectLoop() {
    while (running_) {
        cv::Mat frame;
        {
            std::unique_lock<std::mutex> lock(mutex_);
            cv_.wait(lock, [&] { return !frame_queue_.empty() || !running_; });
            if (!running_) break;
            frame = frame_queue_.front();
            frame_queue_.pop();
        }

        detect(frame);  // 原有的检测逻辑
    }
}

void YoloDetector::Impl::start() {
    running_ = true;
    thread_ = std::thread(&Impl::detectLoop, this);
}

void YoloDetector::Impl::stop() {
    running_ = false;
    cv_.notify_all();
    if (thread_.joinable())
        thread_.join();
}








YoloDetector::YoloDetector() : impl_(new Impl) {}
YoloDetector::~YoloDetector() { delete impl_; }

bool YoloDetector::loadModel(const std::string& param_path, const std::string& bin_path) {
    return impl_->loadModel(param_path, bin_path);
}

int YoloDetector::detect(const cv::Mat& image) {
    return impl_->detect(image);
}

void YoloDetector::setCallback(DetectionCallback callback) {
    impl_->setCallback(callback);
}

void YoloDetector::start() {
    impl_->start();
}

void YoloDetector::stop() {
    impl_->stop();
}

void YoloDetector::enqueueFrame(const cv::Mat& image) {
    impl_->enqueueFrame(image);
}


