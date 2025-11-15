#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>

using namespace std::chrono_literals;

class HelloService : public rclcpp::Node
{

    private:

        bool orin_on = false;
        std::string orin_on_topic;
        double topic_hz = 10.0;

        rclcpp::TimerBase::SharedPtr timer;
        rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr hello_pub;
        
        void sendOrinOn();

        void loadParameters();
        std::string getLaunchNameFromMission();
    
    public:
    
        HelloService();
        ~HelloService() {};
};