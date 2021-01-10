# CAN_tests
Communication between robot and PC through CAN device using ROS.

Aim of this project is to convert ROS twist messages in to CAN dataframe and decode CAN dataframes to ROS messages for Odom data.


schematic :
PC(ROS) <-> virtual CAN <-> Robot

what package does is :
ROS[Twist] -> CAN[Twist] and CAN[Odometry] -> ROS[Odometry]
