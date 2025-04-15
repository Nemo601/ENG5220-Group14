// classifier.hpp
class Classifier {
public:
    explicit Classifier(const std::string& model_path);
    std::string classify(const cv::Mat& image);
private:
    cv::dnn::Net net;
};
