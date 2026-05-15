cmake_minimum_required(VERSION 3.8)
project(my_robot_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 1. FIND DEPENDENCIES
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
# ADDED: Find the standard services package
find_package(std_srvs REQUIRED) 

# 2. ADD EXECUTABLES
add_executable(sensor_publisher src/sensor_publisher.cpp)
add_executable(robot_controller src/robot_controller.cpp)
# ADDED: Your new motor service node
add_executable(motor_service src/motor_service.cpp)

# Require C++17 for all nodes
target_compile_features(sensor_publisher PUBLIC c_std_99 cxx_std_17)  
target_compile_features(robot_controller PUBLIC c_std_99 cxx_std_17)
target_compile_features(motor_service PUBLIC c_std_99 cxx_std_17)

# 3. LINK DEPENDENCIES 
ament_target_dependencies(sensor_publisher rclcpp std_msgs)
ament_target_dependencies(robot_controller rclcpp std_msgs)
# ADDED: Link the motor service to rclcpp and std_srvs
ament_target_dependencies(motor_service rclcpp std_srvs)

# 4. INSTALL TARGETS
install(TARGETS 
  sensor_publisher
  robot_controller
  motor_service   # ADDED: Ensure the service node gets installed
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch DESTINATION share/${PROJECT_NAME}/)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()