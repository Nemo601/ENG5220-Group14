#include "GarbageSorter.h"
#include <iostream>
#include <chrono>
#include <thread>

GarbageSorter::GarbageSorter(const std::vector<std::vector<int>>& motorPins) {
    initializeMotors(motorPins);
    systemBusy = false;
}

GarbageSorter::~GarbageSorter() {
    stopSystem();
}

void GarbageSorter::initializeMotors(const std::vector<std::vector<int>>& motorPins) {
    for (const auto& pins : motorPins) {
        motors.emplace_back(std::make_unique<StepperMotor>(pins));
    }
}

void GarbageSorter::startSystem() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (statusCallback) {
        statusCallback("The waste sorting system has been activated");
    }
}

void GarbageSorter::stopSystem() {
    waitUntilIdle(); // Waiting for the current task to complete
    resetMotors();
    if (statusCallback) {
        statusCallback("The waste sorting system has been discontinued");
    }
}

void GarbageSorter::processWaste(WasteType type) {
    std::unique_lock<std::mutex> lock(mutex_);
    
    // Waiting for the system to idle
    cv_.wait(lock, [this]() { return !systemBusy.load(); });
    
    systemBusy = true;
    
    if (statusCallback) {
        std::string msg;
        switch(type) {
            case RECYCLABLE: msg = "Disposal of recyclable waste"; break;
            case ORGANIC: msg = "Disposal of organic waste"; break;
            case HAZARDOUS: msg = "Disposal of hazardous waste"; break;
            case OTHER: msg = "Disposal of other waste"; break;
        }
        statusCallback(msg);
    }
    
    lock.unlock();
    executeMotorAction(type);
}

void GarbageSorter::executeMotorAction(WasteType type) {
    auto completionCallback = [this, type]() {
        std::string msg;
        switch(type) {
            case RECYCLABLE: msg = "Recyclable waste disposal completed"; break;
            case ORGANIC: msg = "Organic waste disposal completed"; break;
            case HAZARDOUS: msg = "Hazardous waste disposal completed"; break;
            case OTHER: msg = "Other waste disposal completed"; break;
        }
        
        if (statusCallback) {
            statusCallback(msg);
        }
        
        resetMotors();
        notifyCompletion();
    };
    
    switch(type) {
        case RECYCLABLE:
            motors[0]->rotate(500, true);
            motors[1]->rotate(500, true);
            scheduleTask(1, [this, completionCallback]() {
                motors[0]->rotate(500, false);
                motors[1]->rotate(500, false);
                completionCallback();
            });
            break;
            
        case ORGANIC:
            motors[1]->rotate(1000, true);
            scheduleTask(1, [this, completionCallback]() {
                motors[1]->rotate(1000, false);
                completionCallback();
            });
            break;
            
        case HAZARDOUS:
            motors[0]->rotate(100, true);
            scheduleTask(1, [this, completionCallback]() {
                motors[0]->rotate(100, false);
                completionCallback();
            });
            break;
            
        case OTHER:
            motors[3]->rotate(100, true);
            scheduleTask(1, [this, completionCallback]() {
                motors[3]->rotate(100, false);
                completionCallback();
            });
            break;
    }
}

void GarbageSorter::notifyCompletion() {
    std::lock_guard<std::mutex> lock(mutex_);
    systemBusy = false;
    cv_.notify_all(); // Notify all waiting threads
}

void GarbageSorter::resetMotors() {
    for (auto& motor : motors) {
        motor->release();
    }
}

void GarbageSorter::setStatusCallback(std::function<void(const std::string&)> callback) {
    statusCallback = callback;
}

bool GarbageSorter::isBusy() const {
    return systemBusy.load();
}

void GarbageSorter::waitUntilIdle() {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this]() { return !systemBusy.load(); });
}
