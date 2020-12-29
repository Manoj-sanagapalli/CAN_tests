cmake_minimum_required(VERSION 3.0.2)
project(can_tests)


## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs nav_msgs)





## Declare a catkin package
catkin_package()


## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(transmit_node src/transmit.cpp)
target_link_libraries(transmit_node ${catkin_LIBRARIES})

add_executable(recieve_node src/recieve.cpp)
target_link_libraries(recieve_node ${catkin_LIBRARIES})
