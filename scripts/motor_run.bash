# ros2 topic pub --once /motor_command serial_motor_demo_msgs/msg/MotorCommand "{is_pwm: true, mot_1_req_rad_sec: 255, mot_2_req_rad_sec : 255}"

# ros2 run serial_motor_demo driver --ros-args -p encoder_cpr:=3440 -p loop_rate:=30 -p serial_port:=/dev/ttyUSB0 -p baud_rate:=57600

# ## Terminal 1
# $ ros2 run joy joy_node

# ## Terminal 2
# $ ros2 run ps_ros2_common joy_test

# ## Terminal 3
# $ ros2 topic echo /output

ros2 launch ps4_controller ps4_node.launch.py

# CE:2A:26:5F:E7:15

# ros2 topic pub --once /motor_command serial_motor_demo_msgs/msg/MotorCommand "{is_pwm: true, speed_left: -255, speed_right: -255}"