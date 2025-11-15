#include  <hello_service_ros/hello_service_ros.hpp>

HelloService::HelloService() : Node("hello_service_ros")
{
    loadParameters();
    rclcpp::QoS qos(rclcpp::KeepLast(1));
    qos.reliability(RMW_QOS_POLICY_RELIABILITY_RELIABLE);

    RCLCPP_INFO(this->get_logger(), "HelloService initialized - orin_on: %s, topic: %s, hz: %.1f", 
                this->orin_on ? "true" : "false", this->orin_on_topic.c_str(), this->topic_hz);
    
    timer = this->create_wall_timer(std::chrono::duration<double>(1.0 / this->topic_hz), std::bind(&HelloService::sendOrinOn, this));
    hello_pub = this->create_publisher<std_msgs::msg::Bool>(this->orin_on_topic, qos);
}

void HelloService::loadParameters()
{
    // Load parameters from the parameter server  
    this->declare_parameter("orin_on_topic", "/orin/on");
    this->declare_parameter("orin_on", false);
    this->declare_parameter("topic_hz", 10.0);
    
    this->get_parameter("orin_on_topic", this->orin_on_topic);
    this->get_parameter("orin_on", this->orin_on);
    this->get_parameter("topic_hz", this->topic_hz);
}

void HelloService::sendOrinOn()
{
    if (!this->orin_on)
    {
        RCLCPP_INFO_ONCE(this->get_logger(), "Timer callback running but orin_on is false - not publishing");
        return;
    }

    RCLCPP_INFO(this->get_logger(), "Publishing ORIN ON message");
    std_msgs::msg::Bool orin;
    orin.data = true;
    hello_pub->publish(orin);
}