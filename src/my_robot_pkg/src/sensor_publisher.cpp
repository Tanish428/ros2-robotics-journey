#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64.hpp>
#include <cmath>

class SensorPublisher : public rclcpp::Node {
public:
  SensorPublisher() : Node("sensor_publisher"), count_(0) {
    publisher_ = create_publisher<std_msgs::msg::Float64>(
      "/ultrasonic_distance", 10);
    timer_ = create_wall_timer(
      std::chrono::milliseconds(500),
      std::bind(&SensorPublisher::publishDistance, this));
    RCLCPP_INFO(get_logger(), "Sensor publisher ready");
  }
private:
  void publishDistance() {
    auto msg = std_msgs::msg::Float64();
    // Simulate oscillating distance reading
    msg.data = 50.0 + 30.0 * std::sin(count_ * 0.2);
    count_++;
    publisher_->publish(msg);
    RCLCPP_INFO(get_logger(), "Distance: %.2f cm", msg.data);
  }
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  int count_;
};

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SensorPublisher>());
  rclcpp::shutdown(); return 0;
}