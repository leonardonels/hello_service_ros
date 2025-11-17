#include <hello_service_ros/hello_service_ros.hpp>
#include <thread>

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto temp_node = std::make_shared<rclcpp::Node>("temp_param_node");
  temp_node->declare_parameter("node_active_duration", 5.0);
  temp_node->declare_parameter("node_pause_duration", 3.0);
  
  double active_duration = temp_node->get_parameter("node_active_duration").as_double();
  double pause_duration = temp_node->get_parameter("node_pause_duration").as_double();
  
  RCLCPP_INFO(temp_node->get_logger(), "Parametri: attivo=%.1fs, pausa=%.1fs", 
              active_duration, pause_duration);
  
  temp_node.reset();

  while (rclcpp::ok())
  {    
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
    
    std::this_thread::sleep_for(std::chrono::duration<double>(pause_duration));
  }

  rclcpp::shutdown();

  return 0;
}