#include <hello_service_ros/hello_service_ros.hpp>
#include <thread>

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  
  auto temp_node = std::make_shared<rclcpp::Node>("temp_param_node");
  temp_node->declare_parameter("node_active_duration", 5.0);
  temp_node->declare_parameter("node_pause_duration", 3.0);
  temp_node->declare_parameter("keep_running", false);
  
  double active_duration = temp_node->get_parameter("node_active_duration").as_double();
  double pause_duration = temp_node->get_parameter("node_pause_duration").as_double();
  bool keep_running = temp_node->get_parameter("keep_running").as_bool();
  
  RCLCPP_INFO(temp_node->get_logger(), "Parameters: active=%.1fs, pause=%.1fs", 
              active_duration, pause_duration);
  
  temp_node.reset();
  rclcpp::shutdown();

  if(keep_running)
  {
    RCLCPP_INFO(rclcpp::get_logger("main"), "Continuous execution of HelloService node with pauses");
    while (keep_running)
    {
      RCLCPP_INFO(rclcpp::get_logger("main"), "=== INIT ROS2 and node creation ===");
      rclcpp::init(argc, argv);
      
      auto node = std::make_shared<HelloService>();
      
      auto start_time = std::chrono::steady_clock::now();
      auto duration = std::chrono::duration<double>(active_duration);
      
      while (rclcpp::ok() && 
             (std::chrono::steady_clock::now() - start_time) < duration)
      {
        rclcpp::spin_some(node);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }
      
      node.reset();
      rclcpp::shutdown();
      
      std::cout << "Pause of " << pause_duration << " seconds..." << std::endl;
      std::this_thread::sleep_for(std::chrono::duration<double>(pause_duration));
    }
  }

  RCLCPP_INFO(rclcpp::get_logger("main"), "Single execution of HelloService node");
  rclcpp::init(argc, argv);
  
  auto node = std::make_shared<HelloService>();
  rclcpp::spin(node);
  
  rclcpp::shutdown();
  return 0;
}