#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64.hpp>
#include <std_msgs/msg/string.hpp>

class RobotController : public rclcpp::Node {
public:
  RobotController() : Node("robot_controller") {
    subscription_ = create_subscription<std_msgs::msg::Float64>(
      "/ultrasonic_distance", 10,
      std::bind(&RobotController::distanceCallback, this,
      std::placeholders::_1));
    cmd_pub_ = create_publisher<std_msgs::msg::String>("/robot_cmd", 10);
  }
private:
  void distanceCallback(const std_msgs::msg::Float64::SharedPtr msg) {
    auto cmd = std_msgs::msg::String();
    if (msg->data < 15.0) {
      cmd.data = "EMERGENCY_STOP";
    } else if (msg->data < 30.0) {
      cmd.data = "SLOW_AND_TURN";
    } else {
      cmd.data = "MOVE_FORWARD";
    }
    RCLCPP_INFO(get_logger(), "Dist: %.1f → CMD: %s",
      msg->data, cmd.data.c_str());
    cmd_pub_->publish(cmd);
  }
  rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr cmd_pub_;
};

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RobotController>());
  rclcpp::shutdown(); return 0;
}