#include <hello_service_ros/hello_service_ros.hpp>

int main(int argc, char * argv[])
{
  /* node initialization */
  rclcpp::init(argc, argv);

  auto node = std::make_shared<HelloService>();
  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}