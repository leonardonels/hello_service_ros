from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument
import os


def generate_launch_description():

    ld = LaunchDescription()

    config_node = os.path.join(
        get_package_share_directory('as_drive'),
        'config',
        'as_drive.yaml'
        )

    node=Node(
            package='as_drive',
            name='as_drive_node',
            executable='as_drive_node',
            output="screen",
            parameters=[config_node]
        )

    ld.add_action(node)
    return ld