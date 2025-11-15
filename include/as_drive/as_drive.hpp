#include <rclcpp/rclcpp.hpp>
#include <rclcpp/exceptions.hpp>
#include <std_msgs/msg/int8.hpp>
#include <std_msgs/msg/bool.hpp>
#include <unistd.h>

using namespace std::chrono_literals;

class AsDrive : public rclcpp::Node
{

    private:

        std::string as_topic, mission_topic, orin_on_topic, canopen_op_mode_topic;
        pid_t sensors_pid, perception_pid, driving_stack_pid;
        int mission_id;

        bool use_mission_topic, orin_on = false;
        int as_status = -1, as_status_old = -1;

        rclcpp::TimerBase::SharedPtr timer;
        rclcpp::TimerBase::SharedPtr orchestrator;
        rclcpp::Subscription<std_msgs::msg::Int8>::SharedPtr as_sub_, mission_sub_, canopen_op_sub_;
        rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr orin_pub;
        
        void sendOrinOn();

        void loadParameters();
        std::string getLaunchNameFromMission();
    
    public:
    
        AsDrive();
        ~AsDrive() {};
};