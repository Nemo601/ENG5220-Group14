#ifndef GARBAGESORTER_H
#define GARBAGESORTER_H

#include "StepperMotor.h"
#include "Timer.h"
#include <atomic>
#include <functional>
#include <vector>
#include <memory>
#include <mutex>
#include <condition_variable>

class GarbageSorter {
public:
    enum WasteType {
        RECYCLABLE = 1,    // recyclable waste
        ORGANIC,           // organic waste
        HAZARDOUS,         // hazardous waste
        OTHER              // Other rubbish
    };
    
    GarbageSorter(const std::vector<std::vector<int>>& motorPins);
    ~GarbageSorter();
    
    void startSystem();
    void stopSystem();
    void processWaste(WasteType type);
    
    // Setting State Callback Functions
    void setStatusCallback(std::function<void(const std::string&)> callback);
    
    // Getting system status
    bool isBusy() const;
    
    // Waiting for the current task to complete
    void waitUntilIdle();
    
private:
    void initializeMotors(const std::vector<std::vector<int>>& motorPins);
    void executeMotorAction(WasteType type);
    void resetMotors();
    void notifyCompletion();
    
    std::vector<std::unique_ptr<StepperMotor>> motors;
    std::atomic<bool> systemBusy;
    std::function<void(const std::string&)> statusCallback;
    
    // Add mutex locks and condition variables for waiting
    std::mutex mutex_;
    std::condition_variable cv_;
};

#endif // GARBAGESORTER_H