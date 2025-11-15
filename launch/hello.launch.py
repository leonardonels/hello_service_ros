from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
import os


def generate_launch_description():

    ld = LaunchDescription()

    params = os.path.join(
        get_package_share_directory('hello_service_ros'),
        'config',
        'config.yaml'
        )

    node=Node(
            package='hello_service_ros',
            name='hello_service_ros_node',
            executable='hello_service_ros_node',
            output="screen",
            parameters=[params]
        )

    ld.add_action(node)
    return ld