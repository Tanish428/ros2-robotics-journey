cmake_minimum_required(VERSION 3.8)
project(my_robot_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 1. FIND DEPENDENCIES
# You must tell CMake to look for the ROS 2 libraries you used in your C++ code.
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# 2. ADD EXECUTABLES
# This tells CMake where your new C++ files are located.
add_executable(sensor_publisher src/sensor_publisher.cpp)
add_executable(robot_controller src/robot_controller.cpp)

# Require C++17 for both nodes (Standard for ROS 2)
target_compile_features(sensor_publisher PUBLIC c_std_99 cxx_std_17)  
target_compile_features(robot_controller PUBLIC c_std_99 cxx_std_17)

# 3. LINK DEPENDENCIES 
# This links the libraries you found in Step 1 to your specific executables.
ament_target_dependencies(sensor_publisher rclcpp std_msgs)
ament_target_dependencies(robot_controller rclcpp std_msgs)

# 4. INSTALL TARGETS
# This puts the compiled nodes in a folder where the 'ros2 run' command can find them.
install(TARGETS 
  sensor_publisher
  robot_controller
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()