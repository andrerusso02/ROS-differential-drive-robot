#include "Config.h"

#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <ros/time.h>


double ROS_cmd_vel_left = 0;
double ROS_cmd_vel_right = 0;


void ROS_updateWheelsVelocitiesCommands(const geometry_msgs::Twist& msg)
{
    double vLinear = msg.linear.x;
    double vAngular = msg.angular.z;

    ROS_cmd_vel_left = vLinear - vAngular * RobotModel::width / 2.0;
    ROS_cmd_vel_right = vLinear + vAngular * RobotModel::width / 2.0;
}


ros::NodeHandle ROS_nodeHandle;
ros::Subscriber<geometry_msgs::Twist> subCmdVel("/cmd_vel", ROS_updateWheelsVelocitiesCommands);


void ROS_init()
{
    ROS_nodeHandle.initNode();
    ROS_nodeHandle.subscribe(subCmdVel);
}



