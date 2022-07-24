#include "ddbot_base/ddbot_hardware.h"

#include <controller_manager/controller_manager.h>
#include <ros/ros.h>


int main(int argc, char *argv[])
{
    
    // Initialize the ROS node
    ros::init(argc, argv, "ddbot_base");
    ros::NodeHandle nh;

    // Create instance of the robot
    DdbotHardware ddbot(nh);

    // Create an instance of the controller manager and pass it the robot, so that it can handle its resources.
    controller_manager::ControllerManager cm(&ddbot);



    // 1 Hz rate
    ros::Rate rate(1.0); 
    rate.sleep();

    // Blocks until shutdown signal recieved
    while (ros::ok())
    {

        ddbot.test();

        rate.sleep();
    }

    return 0;
}