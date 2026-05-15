#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64.hpp>
#include <std_msgs/msg/string.hpp>

class RobotController : public rclcpp::Node {
public:
  RobotController() : Node("robot_controller") {
    
    // --- ADDED: Declare parameters with default values ---
    this->declare_parameter("stop_distance", 15.0);
    this->declare_parameter("slow_distance", 30.0);
    this->declare_parameter("max_speed", 100);

    subscription_ = this->create_subscription<std_msgs::msg::Float64>(
      "/ultrasonic_distance", 10,
      std::bind(&RobotController::distanceCallback, this, std::placeholders::_1));
      
    cmd_pub_ = this->create_publisher<std_msgs::msg::String>("/robot_cmd", 10);
  }

private:
  void distanceCallback(const std_msgs::msg::Float64::SharedPtr msg) {
    
    // --- ADDED: Read the current parameter values every time a message arrives ---
    double stop_dist = this->get_parameter("stop_distance").as_double();
    double slow_dist = this->get_parameter("slow_distance").as_double();

    auto cmd = std_msgs::msg::String();
    
    // --- UPDATED: Replaced hardcoded numbers with your new dynamic parameters ---
    if (msg->data < stop_dist) {
      cmd.data = "EMERGENCY_STOP";
    } else if (msg->data < slow_dist) {
      cmd.data = "SLOW_AND_TURN";
    } else {
      cmd.data = "MOVE_FORWARD";
    }
    
    RCLCPP_INFO(this->get_logger(), "Dist: %.1f → CMD: %s", msg->data, cmd.data.c_str());
    cmd_pub_->publish(cmd);
  }
  
  rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr cmd_pub_;
};

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RobotController>());
  rclcpp::shutdown(); 
  return 0;
}