#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/set_bool.hpp>

class MotorService : public rclcpp::Node {
public:
  MotorService() : Node("motor_service"), motors_enabled_(false) {
    service_ = create_service<std_srvs::srv::SetBool>(
      "enable_motors",
      std::bind(&MotorService::handleRequest, this,
      std::placeholders::_1, std::placeholders::_2));
    RCLCPP_INFO(get_logger(), "Motor service ready");
  }
private:
  void handleRequest(const std_srvs::srv::SetBool::Request::SharedPtr req,
    std_srvs::srv::SetBool::Response::SharedPtr res) {
    motors_enabled_ = req->data;
    res->success = true;
    res->message = motors_enabled_ ? "Motors ON" : "Motors OFF";
    RCLCPP_INFO(get_logger(), "%s", res->message.c_str());
  }
  rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr service_;
  bool motors_enabled_;
};

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MotorService>());
  rclcpp::shutdown(); return 0;
}