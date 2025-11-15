#include <as_drive/as_drive.hpp>

void handleSignal(int signal) {
    if (signal == SIGINT) {
        std::cout << "Received SIGINT. Killing canbus_bridge process.\n";
        rclcpp::shutdown();
    }
}


int main(int argc, char * argv[])
{
  signal(SIGINT, handleSignal);
  /* node initialization */
  rclcpp::init(argc, argv);

  /* Manage possible error on CAN_BUS Connection */
  try
  {
    auto node = std::make_shared<AsDrive>();
    rclcpp::spin(node);
    rclcpp::shutdown();
  }
  catch(const rclcpp::exceptions::InvalidNodeError& e)
  {
    std::cerr << e.what() << '\n';
  }
  


  return 0;
}