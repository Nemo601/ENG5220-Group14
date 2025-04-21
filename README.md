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

## 📷 Sneak Peek

| System Demo | Architecture Diagram |
|-------------|-----------------------|
| *(Image coming soon)* | *(Diagram coming soon)* |

🎬 Demo video to be uploaded soon!

---

## 🧩 Table of Contents

- [Installation](#installation)
- [Hardware Requirements](#hardware-requirements)
- [System Architecture & Realtime Design](#system-architecture--realtime-design)
- [Build & Run](#build--run)
- [Software Testing](#software-testing)
- [Social Media & Publicity](#social-media--publicity)
- [Acknowledgements](#acknowledgements)
- [Team Members](#team-members)
- [Contact](#contact)

---

## 📦 Installation

Recommended OS: Raspberry Pi OS (64-bit) / Ubuntu 22.04

Install required dependencies:

```bash
sudo apt-get update
sudo apt-get install -y cmake g++ libopencv-dev wiringpi libjpeg-dev libpng-dev

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

*To be updated...*  
👉 This section will describe:
- Event-driven mechanisms for sensor input
- Callback or threading logic used in motor control
- Real-time scheduling or prioritization if any
- Visual classification model integration (e.g., TensorFlow Lite or OpenCV)

---

## 🛠️ Build & Run

### Compile the Project

```bash
cmake .
make
```

### Execute

```bash
./bin/intelligent-bin
```

---

## 🧪 Software Testing

*To be updated...*  
We plan to include:
- Unit tests for each sensor driver
- Demo script for classification scenarios
- Performance logs of recognition latency and bin-switching time

---

## 📣 Social Media & Publicity

Follow us on:

[Instagram](https://www.instagram.com/sortmateteam14?igsh=MXgzd2pqbmxndG1vdA==)

[TikTok](https://www.tiktok.com/@sortmateteam14?_t=ZN-8vYeORF6HlG&_r=1)


Let us know if you'd like to feature or test our prototype!

---

## 🙏 Acknowledgements

We would like to thank:
- **Dr. Bernd Porr** – for his real-time systems expertise and guidance  
- **ENG5220 Teaching Team** – for technical feedback and lab support  
- Our peers – for inspiration and friendly competition!

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
