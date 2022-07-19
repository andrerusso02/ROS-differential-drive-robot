#include "Config.h"

#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <std_msgs/Int16.h>
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
std_msgs::Int16 ROS_cnt_ticks_left;
std_msgs::Int16 ROS_cnt_ticks_right;

ros::Subscriber<geometry_msgs::Twist> subCmdVel("/cmd_vel", ROS_updateWheelsVelocitiesCommands);


ros::Publisher pub_encoder_ticks_left("/lwheel", &ROS_cnt_ticks_left);
ros::Publisher pub_encoder_ticks_right("/rwheel", &ROS_cnt_ticks_right);


void ROS_init()
{
    ROS_nodeHandle.initNode();
    ROS_nodeHandle.subscribe(subCmdVel);
    ROS_nodeHandle.advertise(pub_encoder_ticks_left);
    ROS_nodeHandle.advertise(pub_encoder_ticks_right);
}


void publish_encoders_ticks(volatile long *nb_ticks_encoder_l, volatile long *nb_ticks_encoder_r)
{
    ROS_cnt_ticks_left.data = *nb_ticks_encoder_l;
    ROS_cnt_ticks_right.data = *nb_ticks_encoder_r;
    pub_encoder_ticks_left.publish(&ROS_cnt_ticks_left);
    pub_encoder_ticks_right.publish(&ROS_cnt_ticks_right);
}



