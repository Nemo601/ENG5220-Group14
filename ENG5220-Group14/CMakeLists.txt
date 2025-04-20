cmake_minimum_required(VERSION 3.10)
project(v5lite_s1_demo)

# Setting the C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable OpenMP (corresponds to -fopenmp)
find_package(OpenMP REQUIRED)
if(OpenMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# Find OpenCV (corresponds to `pkg-config --cflags --libs opencv4`)
find_package(OpenCV REQUIRED)

#find wiringpi
find_library(WIRINGPI_LIB wiringPi)

# Adding an executable file
add_executable(ENG5220
    src/CameraTimer.cpp
    src/CameraWorker.cpp
    src/CameraCapture.cpp
    src/ThreadController.cpp
    src/GarbageSorter.cpp 
    src/StepperMotor.cpp 
    src/Timer.cpp
    src/main.cpp
    src/yolo_detector.cpp
)

# Include NCNN header files (corresponding to -I/ncnn/build/install/include/ncnn)
target_include_directories(ENG5220 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIR}
    ${NCNN_INCLUDE_DIR}
)

# Link OpenCV and NCNN libraries (corresponding to -L/home/pi/ncnn/build/install/lib -lncnn)
target_link_directories(ENG5220 PRIVATE
    {NCNN_LIBRARY}
)

target_link_libraries(ENG5220 PRIVATE
    ncnn
    ${OpenCV_LIBS}
    OpenMP::OpenMP_CXX
    ${WIRINGPI_LIB}
)
