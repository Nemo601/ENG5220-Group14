# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/ENG5220

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/ENG5220

# Include any dependencies generated for this target.
include CMakeFiles/ENG5220.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ENG5220.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ENG5220.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ENG5220.dir/flags.make

CMakeFiles/ENG5220.dir/src/CameraTimer.cpp.o: CMakeFiles/ENG5220.dir/flags.make
CMakeFiles/ENG5220.dir/src/CameraTimer.cpp.o: src/CameraTimer.cpp
CMakeFiles/ENG5220.dir/src/CameraTimer.cpp.o: CMakeFiles/ENG5220.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/ENG5220/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ENG5220.dir/src/CameraTimer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ENG5220.dir/src/CameraTimer.cpp.o -MF CMakeFiles/ENG5220.dir/src/CameraTimer.cpp.o.d -o CMakeFiles/ENG5220.dir/src/CameraTimer.cpp.o -c /home/pi/ENG5220/src/CameraTimer.cpp

CMakeFiles/ENG5220.dir/src/CameraTimer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ENG5220.dir/src/CameraTimer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/ENG5220/src/CameraTimer.cpp > CMakeFiles/ENG5220.dir/src/CameraTimer.cpp.i

CMakeFiles/ENG5220.dir/src/CameraTimer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ENG5220.dir/src/CameraTimer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/ENG5220/src/CameraTimer.cpp -o CMakeFiles/ENG5220.dir/src/CameraTimer.cpp.s

CMakeFiles/ENG5220.dir/src/CameraWorker.cpp.o: CMakeFiles/ENG5220.dir/flags.make
CMakeFiles/ENG5220.dir/src/CameraWorker.cpp.o: src/CameraWorker.cpp
CMakeFiles/ENG5220.dir/src/CameraWorker.cpp.o: CMakeFiles/ENG5220.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/ENG5220/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ENG5220.dir/src/CameraWorker.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ENG5220.dir/src/CameraWorker.cpp.o -MF CMakeFiles/ENG5220.dir/src/CameraWorker.cpp.o.d -o CMakeFiles/ENG5220.dir/src/CameraWorker.cpp.o -c /home/pi/ENG5220/src/CameraWorker.cpp

CMakeFiles/ENG5220.dir/src/CameraWorker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ENG5220.dir/src/CameraWorker.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/ENG5220/src/CameraWorker.cpp > CMakeFiles/ENG5220.dir/src/CameraWorker.cpp.i

CMakeFiles/ENG5220.dir/src/CameraWorker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ENG5220.dir/src/CameraWorker.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/ENG5220/src/CameraWorker.cpp -o CMakeFiles/ENG5220.dir/src/CameraWorker.cpp.s

CMakeFiles/ENG5220.dir/src/CameraCapture.cpp.o: CMakeFiles/ENG5220.dir/flags.make
CMakeFiles/ENG5220.dir/src/CameraCapture.cpp.o: src/CameraCapture.cpp
CMakeFiles/ENG5220.dir/src/CameraCapture.cpp.o: CMakeFiles/ENG5220.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/ENG5220/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ENG5220.dir/src/CameraCapture.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ENG5220.dir/src/CameraCapture.cpp.o -MF CMakeFiles/ENG5220.dir/src/CameraCapture.cpp.o.d -o CMakeFiles/ENG5220.dir/src/CameraCapture.cpp.o -c /home/pi/ENG5220/src/CameraCapture.cpp

CMakeFiles/ENG5220.dir/src/CameraCapture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ENG5220.dir/src/CameraCapture.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/ENG5220/src/CameraCapture.cpp > CMakeFiles/ENG5220.dir/src/CameraCapture.cpp.i

CMakeFiles/ENG5220.dir/src/CameraCapture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ENG5220.dir/src/CameraCapture.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/ENG5220/src/CameraCapture.cpp -o CMakeFiles/ENG5220.dir/src/CameraCapture.cpp.s

CMakeFiles/ENG5220.dir/src/ThreadController.cpp.o: CMakeFiles/ENG5220.dir/flags.make
CMakeFiles/ENG5220.dir/src/ThreadController.cpp.o: src/ThreadController.cpp
CMakeFiles/ENG5220.dir/src/ThreadController.cpp.o: CMakeFiles/ENG5220.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/ENG5220/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ENG5220.dir/src/ThreadController.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ENG5220.dir/src/ThreadController.cpp.o -MF CMakeFiles/ENG5220.dir/src/ThreadController.cpp.o.d -o CMakeFiles/ENG5220.dir/src/ThreadController.cpp.o -c /home/pi/ENG5220/src/ThreadController.cpp

CMakeFiles/ENG5220.dir/src/ThreadController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ENG5220.dir/src/ThreadController.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/ENG5220/src/ThreadController.cpp > CMakeFiles/ENG5220.dir/src/ThreadController.cpp.i

CMakeFiles/ENG5220.dir/src/ThreadController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ENG5220.dir/src/ThreadController.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/ENG5220/src/ThreadController.cpp -o CMakeFiles/ENG5220.dir/src/ThreadController.cpp.s

CMakeFiles/ENG5220.dir/src/GarbageSorter.cpp.o: CMakeFiles/ENG5220.dir/flags.make
CMakeFiles/ENG5220.dir/src/GarbageSorter.cpp.o: src/GarbageSorter.cpp
CMakeFiles/ENG5220.dir/src/GarbageSorter.cpp.o: CMakeFiles/ENG5220.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/ENG5220/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ENG5220.dir/src/GarbageSorter.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ENG5220.dir/src/GarbageSorter.cpp.o -MF CMakeFiles/ENG5220.dir/src/GarbageSorter.cpp.o.d -o CMakeFiles/ENG5220.dir/src/GarbageSorter.cpp.o -c /home/pi/ENG5220/src/GarbageSorter.cpp

CMakeFiles/ENG5220.dir/src/GarbageSorter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ENG5220.dir/src/GarbageSorter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/ENG5220/src/GarbageSorter.cpp > CMakeFiles/ENG5220.dir/src/GarbageSorter.cpp.i

CMakeFiles/ENG5220.dir/src/GarbageSorter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ENG5220.dir/src/GarbageSorter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/ENG5220/src/GarbageSorter.cpp -o CMakeFiles/ENG5220.dir/src/GarbageSorter.cpp.s

CMakeFiles/ENG5220.dir/src/StepperMotor.cpp.o: CMakeFiles/ENG5220.dir/flags.make
CMakeFiles/ENG5220.dir/src/StepperMotor.cpp.o: src/StepperMotor.cpp
CMakeFiles/ENG5220.dir/src/StepperMotor.cpp.o: CMakeFiles/ENG5220.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/ENG5220/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ENG5220.dir/src/StepperMotor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ENG5220.dir/src/StepperMotor.cpp.o -MF CMakeFiles/ENG5220.dir/src/StepperMotor.cpp.o.d -o CMakeFiles/ENG5220.dir/src/StepperMotor.cpp.o -c /home/pi/ENG5220/src/StepperMotor.cpp

CMakeFiles/ENG5220.dir/src/StepperMotor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ENG5220.dir/src/StepperMotor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/ENG5220/src/StepperMotor.cpp > CMakeFiles/ENG5220.dir/src/StepperMotor.cpp.i

CMakeFiles/ENG5220.dir/src/StepperMotor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ENG5220.dir/src/StepperMotor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/ENG5220/src/StepperMotor.cpp -o CMakeFiles/ENG5220.dir/src/StepperMotor.cpp.s

CMakeFiles/ENG5220.dir/src/Timer.cpp.o: CMakeFiles/ENG5220.dir/flags.make
CMakeFiles/ENG5220.dir/src/Timer.cpp.o: src/Timer.cpp
CMakeFiles/ENG5220.dir/src/Timer.cpp.o: CMakeFiles/ENG5220.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/ENG5220/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/ENG5220.dir/src/Timer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ENG5220.dir/src/Timer.cpp.o -MF CMakeFiles/ENG5220.dir/src/Timer.cpp.o.d -o CMakeFiles/ENG5220.dir/src/Timer.cpp.o -c /home/pi/ENG5220/src/Timer.cpp

CMakeFiles/ENG5220.dir/src/Timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ENG5220.dir/src/Timer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/ENG5220/src/Timer.cpp > CMakeFiles/ENG5220.dir/src/Timer.cpp.i

CMakeFiles/ENG5220.dir/src/Timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ENG5220.dir/src/Timer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/ENG5220/src/Timer.cpp -o CMakeFiles/ENG5220.dir/src/Timer.cpp.s

CMakeFiles/ENG5220.dir/src/main.cpp.o: CMakeFiles/ENG5220.dir/flags.make
CMakeFiles/ENG5220.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/ENG5220.dir/src/main.cpp.o: CMakeFiles/ENG5220.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/ENG5220/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/ENG5220.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ENG5220.dir/src/main.cpp.o -MF CMakeFiles/ENG5220.dir/src/main.cpp.o.d -o CMakeFiles/ENG5220.dir/src/main.cpp.o -c /home/pi/ENG5220/src/main.cpp

CMakeFiles/ENG5220.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ENG5220.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/ENG5220/src/main.cpp > CMakeFiles/ENG5220.dir/src/main.cpp.i

CMakeFiles/ENG5220.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ENG5220.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/ENG5220/src/main.cpp -o CMakeFiles/ENG5220.dir/src/main.cpp.s

CMakeFiles/ENG5220.dir/src/yolo_detector.cpp.o: CMakeFiles/ENG5220.dir/flags.make
CMakeFiles/ENG5220.dir/src/yolo_detector.cpp.o: src/yolo_detector.cpp
CMakeFiles/ENG5220.dir/src/yolo_detector.cpp.o: CMakeFiles/ENG5220.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/ENG5220/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/ENG5220.dir/src/yolo_detector.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ENG5220.dir/src/yolo_detector.cpp.o -MF CMakeFiles/ENG5220.dir/src/yolo_detector.cpp.o.d -o CMakeFiles/ENG5220.dir/src/yolo_detector.cpp.o -c /home/pi/ENG5220/src/yolo_detector.cpp

CMakeFiles/ENG5220.dir/src/yolo_detector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ENG5220.dir/src/yolo_detector.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/ENG5220/src/yolo_detector.cpp > CMakeFiles/ENG5220.dir/src/yolo_detector.cpp.i

CMakeFiles/ENG5220.dir/src/yolo_detector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ENG5220.dir/src/yolo_detector.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/ENG5220/src/yolo_detector.cpp -o CMakeFiles/ENG5220.dir/src/yolo_detector.cpp.s

# Object files for target ENG5220
ENG5220_OBJECTS = \
"CMakeFiles/ENG5220.dir/src/CameraTimer.cpp.o" \
"CMakeFiles/ENG5220.dir/src/CameraWorker.cpp.o" \
"CMakeFiles/ENG5220.dir/src/CameraCapture.cpp.o" \
"CMakeFiles/ENG5220.dir/src/ThreadController.cpp.o" \
"CMakeFiles/ENG5220.dir/src/GarbageSorter.cpp.o" \
"CMakeFiles/ENG5220.dir/src/StepperMotor.cpp.o" \
"CMakeFiles/ENG5220.dir/src/Timer.cpp.o" \
"CMakeFiles/ENG5220.dir/src/main.cpp.o" \
"CMakeFiles/ENG5220.dir/src/yolo_detector.cpp.o"

# External object files for target ENG5220
ENG5220_EXTERNAL_OBJECTS =

ENG5220: CMakeFiles/ENG5220.dir/src/CameraTimer.cpp.o
ENG5220: CMakeFiles/ENG5220.dir/src/CameraWorker.cpp.o
ENG5220: CMakeFiles/ENG5220.dir/src/CameraCapture.cpp.o
ENG5220: CMakeFiles/ENG5220.dir/src/ThreadController.cpp.o
ENG5220: CMakeFiles/ENG5220.dir/src/GarbageSorter.cpp.o
ENG5220: CMakeFiles/ENG5220.dir/src/StepperMotor.cpp.o
ENG5220: CMakeFiles/ENG5220.dir/src/Timer.cpp.o
ENG5220: CMakeFiles/ENG5220.dir/src/main.cpp.o
ENG5220: CMakeFiles/ENG5220.dir/src/yolo_detector.cpp.o
ENG5220: CMakeFiles/ENG5220.dir/build.make
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_stitching.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_alphamat.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_aruco.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_barcode.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_bgsegm.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_bioinspired.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_ccalib.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_cvv.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_dnn_objdetect.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_dnn_superres.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_dpm.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_face.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_freetype.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_fuzzy.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_hdf.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_hfs.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_img_hash.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_intensity_transform.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_line_descriptor.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_mcc.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_quality.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_rapid.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_reg.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_rgbd.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_saliency.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_shape.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_stereo.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_structured_light.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_superres.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_surface_matching.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_tracking.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_videostab.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_viz.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_wechat_qrcode.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_xobjdetect.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_xphoto.so.4.6.0
ENG5220: /usr/local/lib/libwiringPi.so
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_highgui.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_datasets.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_plot.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_text.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_ml.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_phase_unwrapping.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_optflow.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_ximgproc.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_video.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_videoio.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_imgcodecs.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_objdetect.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_calib3d.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_dnn.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_features2d.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_flann.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_photo.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_imgproc.so.4.6.0
ENG5220: /usr/lib/aarch64-linux-gnu/libopencv_core.so.4.6.0
ENG5220: /usr/lib/gcc/aarch64-linux-gnu/12/libgomp.so
ENG5220: /usr/lib/aarch64-linux-gnu/libpthread.a
ENG5220: CMakeFiles/ENG5220.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/ENG5220/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable ENG5220"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ENG5220.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ENG5220.dir/build: ENG5220
.PHONY : CMakeFiles/ENG5220.dir/build

CMakeFiles/ENG5220.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ENG5220.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ENG5220.dir/clean

CMakeFiles/ENG5220.dir/depend:
	cd /home/pi/ENG5220 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/ENG5220 /home/pi/ENG5220 /home/pi/ENG5220 /home/pi/ENG5220 /home/pi/ENG5220/CMakeFiles/ENG5220.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ENG5220.dir/depend

