# 🗑️ Intelligent Classification Rubbish Bin (Team 14) 
**_"Smarter Sorting, Cleaner Future"_**

![LOGO](./LOGO.jpg)

> Real-time Embedded System | Smart Waste Sorting | Environmental Automation | Raspberry Pi

---

## 📌 Project Overview

The **Intelligent Classification Rubbish Bin** is a real-time embedded system designed for efficient and sustainable waste management. Built on the Raspberry Pi platform, the system integrates computer vision and multi-threaded control to automatically detect and sort waste into the correct bins.

Leveraging **YOLOv5 object detection, stepper motor control**, and **timer-based task scheduling**, this smart bin ensures precise, real-time classification and disposal. The architecture follows **SOLID object-oriented design principles**, enabling high modularity, testability, and scalability—making it ideal for both research and real-world deployment.
This project enhances sustainability by promoting automated recycling, reducing human error, and improving overall waste management efficiency.

**Key Features:**
- **Camera-based waste recognition** using YOLOv5 and NCNN inference framework
- **Real-time multi-threaded scheduling** with timer-triggered callbacks
- **Stepper motor-driven bin rotation system**, offering precise control and extensible logic
- **Modular class structure** based on SOLID principles for easy maintenance and future upgrades
- **Decoupled logic and thread-safe data sharing** through callback interfaces


---

## 📦 Installation

Recommended OS: Raspberry Pi OS (64-bit) / Ubuntu 22.04

Install required dependencies:

```bash
sudo apt-get update
sudo apt-get install -y cmake g++ libopencv-dev wiringpi libjpeg-dev libpng-dev
```

---


## 🔧 Hardware Requirements

### Microcontroller
- Raspberry Pi 5

### Sensors
- 1x PCBA H720P 720P camera module with 2.9mm wide-angle lens (5V, 100mA, 1W, 38dB SNR)
- 1x LM393 H2010 photoelectric infrared sensor (5V, 15.6 x 5.5 x 2.3 cm; 20g)

### Motors & Mechanics
- 4x 28BYJ-48 Geared Stepper Motor (5V, torque >34.3 mN·m, 283g, 14.3 x 8.5 x 3.5 cm)
- 4x Flanged Sleeve Bearings (6.35 mm x 15 mm; inner Ø 6.4 mm, outer Ø 9.3 mm)
- DuPont cable sets

### Structure & Assembly
- Acrylic board sheets (7 types, various sizes; see design spec)
- 4x Acrylic round rods (⌀6 mm x 260 mm)
- 48x Clear acrylic panels (from prior version)
- Handheld hacksaw
- Hot glue gun

---

## ⚙️ System Architecture & Realtime Design

This intelligent waste sorting system is built for **event-driven, real-time embedded control** on Raspberry Pi. It adheres to **modular SOLID design** and minimizes latency through efficient thread management and asynchronous callbacks.


### Real-Time Workflow

```plaintext
      ┌──────────────┐
      │  File Watch  │◄── Raspberry Pi monitors /images directory
      └─────┬────────┘
            │
            ▼
     ┌──────────────┐
     │ CameraWorker │───► Periodically captures images via Timer
     └─────┬────────┘
           │
           ▼
     ┌──────────────┐
     │ YoloDetector │───► Detects objects with YOLOv5 (ncnn) and triggers callback
     └─────┬────────┘
           │
           ▼
     ┌──────────────┐
     │GarbageSorter │───► Classifies object and activates stepper motors
     └──────────────┘
```


---

## 🛠️ Build & Run

### Compile the Project

```bash
cmake .
make
```

### Execute

```bash
./bin/sortmate
```

---

## ⚙️ Software Testing

### Camera & Scheduling Test

- **Modules Tested**: `CameraWorker`, `Timer`
- **Focus**: Periodic capture timing, image integrity
- **Outcome**:
  - Capture duration consistently under **500ms**
  - Interval accuracy within **±100ms** of target 2s cycle
  - No missing or corrupted image files in the watch directory


### YOLOv5 Inference Test

- **Modules Tested**: `YoloDetector`, `NCNN`
- **Focus**: Inference time, callback reliability
- **Outcome**:
  - Average detection time: **<800ms** using lightweight v5lite model
  - Callback triggered correctly for all valid inputs
  - Accurate object counts and label consistency across frames


### Stepper Motor Response Test

- **Modules Tested**: `GarbageSorter`, `StepperMotor`
- **Focus**: Actuation timing, motor-thread safety
- **Outcome**:
  - Total rotation and reset time under **1.5s** per item
  - No threading conflicts or motor blocking observed
  - Detected waste types correctly mapped to motor channels


### Sensor Trigger Test

- **Modules Tested**: GPIO input, `main_sort.cpp` startup logic
- **Focus**: Response latency and reliability
- **Outcome**:
  - System activates within **<500ms** after light sensor trigger
  - No false triggers or missed events in continuous testing
  - State transitions from standby → detection → sorting verified


### Summary

All key real-time functions passed their timing targets with safe margins. The use of **modular class structure, mutexes, and callbacks** ensured stable, thread-safe operation in a resource-constrained embedded environment.


---

## 📣 Social Media & Publicity

Follow us on:

[Instagram](https://www.instagram.com/sortmateteam14?igsh=MXgzd2pqbmxndG1vdA==)

[TikTok](https://www.tiktok.com/@sortmateteam14?_t=ZN-8vYeORF6HlG&_r=1)


Let us know if you'd like to feature or test our prototype!

---

## 👏 Acknowledgements

We would like to thank: 
- **Dr. Bernd Porr** — for his dedicated teaching and continuous project support  
- **Thomas O'Hara** — for his help in preparing project materials  
- **ENG5220 Teaching Team** — for technical guidance and lab assistance  
- **Our peers** — for their collaboration, ideas, and motivation throughout the course


---

## 👥 Team Members

- **Xuan Liu** (3029536L)
- **Yuchen Zhang** (3033100Z)
- **Shiao Hu** (3030874H)
- **Huaqi Liu** (3058895L)
- **Baixiang Kong** (2906728K)

---

## 📮 Contact

📧 Email: kongbx0064@gmail.com

📁 License: MIT

📅 Last Updated: 19/04/2025

---

⭐ If you like this project, give us a star and share with your friends. Let's make waste management smarter together!
