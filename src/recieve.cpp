
#include "operations.cpp"
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <iostream>
#include <math.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "recieve_node");
    ros::NodeHandle n;
    ros::Publisher pub_odom = n.advertise<nav_msgs::Odometry>("odom", 1000);
    ros::Rate loop_rate(10);
    while (ros::ok()) {

        //get data from can and store in odom message type
        recieveFrom_can();

        pub_odom.publish(odom);
        loop_rate.sleep();
    }
    return 0;
}