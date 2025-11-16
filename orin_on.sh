#!/bin/bash

source /home/orin/.bashrc
source /opt/ros/humble/setup.bash
source /home/orin/ros2_ws/install/setup.bash

ros2 launch hello_service_ros hello.launch.py &