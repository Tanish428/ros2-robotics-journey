from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
  stop_dist_arg = DeclareLaunchArgument(
    'stop_distance', default_value='15.0')

  sensor_node = Node(
    package='my_robot_pkg',
    executable='sensor_publisher',
    name='sensor')

  controller_node = Node(
    package='my_robot_pkg',
    executable='robot_controller',
    name='controller',
    parameters=[{'stop_distance':
      LaunchConfiguration('stop_distance')}])

  motor_service_node = Node(
    package='my_robot_pkg',
    executable='motor_service')

  return LaunchDescription([
    stop_dist_arg, sensor_node,
    controller_node, motor_service_node])
