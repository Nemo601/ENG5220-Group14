class EventDispatcher {
public:
    using Callback = std::function<void(const std::string&)>;
    void registerCallback(Callback cb);
    void dispatchEvent(const std::string& event);
private:
    std::vector<Callback> callbacks;
};