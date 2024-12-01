from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='joy',
            executable='joy_node'
            # output='screen'
        ),
        
        Node(
            package='ps4_controller',
            executable='ps4_node'
            # output='screen'
        ),

        Node(
            package='serial_motor_demo',
            executable='driver',
            output='screen',
            parameters=[{
                "encoder_cpr": 3440,
                "loop_rate": 30,
                "serial_port": '/dev/ttyUSB0',
                "baud_rate": 57600,
            }]
        )
    ])

if __name__ == '__main__':
    generate_launch_description()
