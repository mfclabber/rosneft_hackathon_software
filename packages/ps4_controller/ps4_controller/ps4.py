import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from serial_motor_demo_msgs.msg import MotorCommand
from sensor_msgs.msg import Joy
# from nav_msgs.msg import Odometry, Path

class PS4ControllerNode(Node):
    def __init__(self):
        super().__init__('ps4_controller_node')
        # self.publisher_ = self.create_publisher(Twist, '/cmd_vel', 10)
        self.publisher_ = self.create_publisher(
                                    MotorCommand,
                                    'motor_command',
                                    10)
        
        self.subscription = self.create_subscription(
                                    Joy,
                                    '/joy',
                                    self.joy_callback,
                                    10)
        # self.subscription  # prevent unused variable warning
        # self.subscription = self.create_subscription(
        #                             Odometry,
        #                             '/ov_msckf/loop_extrinsic',
        #                             self.odometry_callback,
        #                             10)
    # def joy_callback(self, msg): # for Twist msg type
    #     twist = Twist()
    #     twist.linear.x = msg.axes[1]  # Left stick vertical axis
    #     twist.linear.y = msg.axes[3]  # Right stick vertical axis
    #     self.publisher_.publish(twist)

    # def odometry_callback(self, msg):
    #     print(f' X: {msg.pose.pose.position.x}')

    def joy_callback(self, msg): # for Twist msg type
        commands = MotorCommand()
        commands.is_pwm = True
        commands.speed_left = round(-255 * msg.axes[1], 3)  # Left stick vertical axis
        commands.speed_right = round(-255 * msg.axes[4], 3)  # Right stick vertical axis
        self.publisher_.publish(commands)



def main(args=None):
    rclpy.init(args=args)
    ps4_controller_node = PS4ControllerNode()
    rclpy.spin(ps4_controller_node)
    ps4_controller_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
