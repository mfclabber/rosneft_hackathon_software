from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package="surface_builder_map",
            executable="surface_builder_map_node",
            name="surface_builder_map_node",
            output="screen",
            parameters=["/home/itmo/axior_software/packages/surface_builder_map/config/params.yaml"]
        ),
    ])
