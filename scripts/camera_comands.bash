# v4l2-ctl --list-devices --all

# ros2 run v4l2_camera v4l2_camera_node --ros-args -p video_device:="/dev/video0"

# ros2 run realsense2_camera realsense2_camera_node
# ros2 run realsense2_camera realsense2_camera_node --ros-args -p filters:=colorizer


# ros2 launch foxglove_bridge foxglove_bridge_launch.xml

# ros2 run aruco_localization aruco_localization

# ros2 launch realsense2_camera rs_launch.py enable_color:=true enable_gyro:=true enable_accel:=true unite_imu_method:=2 enable_depth:=false

# ros2 launch ov_msckf subscribe.launch.py config:=rs_d455 max_cameras:=1