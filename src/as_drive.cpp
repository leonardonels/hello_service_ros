#include  <as_drive/as_drive.hpp>

AsDrive::AsDrive() : Node("as_drive")
{
    loadParameters();
    rclcpp::QoS qos(rclcpp::KeepLast(1));
    qos.durability(RMW_QOS_POLICY_DURABILITY_TRANSIENT_LOCAL);
    qos.reliability(RMW_QOS_POLICY_RELIABILITY_RELIABLE);

    // Initialize the subscriber
    //as_sub_ = this->create_subscription<std_msgs::msg::Int8>(this->as_topic, qos, std::bind(&AsDrive::asCallback, this, std::placeholders::_1));
    orin_pub = this->create_publisher<std_msgs::msg::Bool>(this->orin_on_topic, qos);

    timer = this->create_wall_timer(100ms, std::bind(&AsDrive::sendOrinOn, this));
    //orchestrator = this->create_wall_timer(100ms, std::bind(&AsDrive::orchestratorOrin, this));
}

void AsDrive::loadParameters()
{
    // Load parameters from the parameter server
    this->declare_parameter("as_topic", "/as_state");
    this->get_parameter("as_topic", this->as_topic);
    
    this->declare_parameter("orin_on_topic", "/orin/on");
    this->get_parameter("orin_on_topic", this->orin_on_topic);
    
    this->declare_parameter("mission_topic", "/as_mission");
    this->get_parameter("mission_topic", this->mission_topic);
    
    this->declare_parameter("mission_id", 4);
    this->get_parameter("mission_id", this->mission_id);
    
    this->declare_parameter("use_mission_sub", false);
    this->get_parameter("use_mission_sub", this->use_mission_topic);
}

void AsDrive::sendOrinOn()
{
    if (!this->orin_on)
        return;
    
    std_msgs::msg::Bool res;
    res.data = true;
    orin_pub->publish(res);
}