
#include "../include/yolo_detector.h"
#include <ncnn/net.h>
#include <cmath>
#include <float.h>
#include <algorithm>

template<typename T>
T clamp(T value, T low, T high) {
    return std::max(low, std::min(value, high));
}

class YoloDetector::Impl {
public:
    Impl();
    ~Impl();

    bool loadModel(const std::string& param_path, const std::string& bin_path);
    int detect(const cv::Mat& image);
    void setCallback(DetectionCallback cb);

private:
    void generateProposals(const ncnn::Mat& anchors, int stride, const ncnn::Mat& in_pad,
                           const ncnn::Mat& feat_blob, float prob_threshold,
                           std::vector<Object>& proposals);

    float sigmoid(float x);
    float unsigmoid(float y);
    float intersectionArea(const Object& a, const Object& b);
    void sortDescending(std::vector<Object>& objs);
    void nms(const std::vector<Object>& proposals, std::vector<int>& picked, float nms_threshold);

private:
    ncnn::Net yolov5_;
    DetectionCallback callback_;
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

float YoloDetector::Impl::sigmoid(float x) { return 1.f / (1.f + exp(-x)); }
float YoloDetector::Impl::unsigmoid(float y) { return -1.0f * log((1.0f / y) - 1.0f); }

float YoloDetector::Impl::intersectionArea(const Object& a, const Object& b) {
    return (a.rect & b.rect).area();
}

void YoloDetector::Impl::sortDescending(std::vector<Object>& objs) {
    std::sort(objs.begin(), objs.end(), [](const Object& a, const Object& b) {
        return a.prob > b.prob;
    });
}

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
        for (int i = 0; i < num_grid_y; i++) {
            for (int j = 0; j < num_grid_x; j++) {
                const float* featptr = feat.row(i * num_grid_x + j);
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
        {"376",   {30,61, 62,45, 59,119}},
        {"401",   {116,90, 156,198, 373,326}}
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

        x0 = clamp(x0, 0.f, (float)(img_w - 1));
        y0 = clamp(y0, 0.f, (float)(img_h - 1));
        x1 = clamp(x1, 0.f, (float)(img_w - 1));
        y1 = clamp(y1, 0.f, (float)(img_h - 1));

        objects[i] = {cv::Rect_<float>(x0, y0, x1 - x0, y1 - y0), obj.label, obj.prob};
    }

    if (callback_) callback_(objects);
    return 0;
}

void YoloDetector::Impl::setCallback(DetectionCallback cb) {
    callback_ = cb;
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
