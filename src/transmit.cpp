#include "operations.cpp"
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <iostream>
#include <math.h>

// Call back function when subscriber gets a message
void callback(const geometry_msgs::Twist& velocity)
{
    // Extracting the data from ROS topics
    V_lin_x = velocity.linear.x;
    V_lin_y = velocity.linear.y;
    V_lin_z = velocity.linear.z;
    V_ang_x = velocity.angular.x;
    V_ang_y = velocity.angular.y;
    V_ang_z = velocity.angular.z;
    
    //Function used to translate the twist data in to CAN frames
    translate(V_lin_x, V_lin_y, V_lin_z, V_ang_x, V_ang_y, V_ang_z);

    // Function to send the CAN frame to CAN device
    sendTo_can();
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "transmit_node");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("cmd_vel", 1000, callback);
    ros::spin();
    return 0;
}
