#include "Config.h"

#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <std_msgs/Float32.h>
#include <ros/time.h>


double ROS_cmd_vel_left = 0;
double ROS_cmd_vel_right = 0;


void ROS_updateRightWheelVelocityCommand(const std_msgs::Float32& msg)
{
  ROS_cmd_vel_right = msg.data;
}

void ROS_updateLeftWheelVelocityCommand(const std_msgs::Float32& msg)
{
  ROS_cmd_vel_left = msg.data;
}




ros::NodeHandle ROS_nodeHandle;
std_msgs::Float32 vel_measured_left;
std_msgs::Float32 vel_measured_right;

//Subscribers
ros::Subscriber<std_msgs::Float32> sub_vel_measured_left("/cmd_vel_motor_l", &ROS_updateLeftWheelVelocityCommand);
ros::Subscriber<std_msgs::Float32> sub_vel_measured_right("/cmd_vel_motor_r", &ROS_updateRightWheelVelocityCommand);

//Publishers
ros::Publisher pub_encoder_ticks_left("/encoder_vel_motor_l", &vel_measured_left);
ros::Publisher pub_encoder_ticks_right("/encoder_vel_motor_r", &vel_measured_right);


void ROS_init()
{
    ROS_nodeHandle.initNode();
    ROS_nodeHandle.subscribe(sub_vel_measured_left);
    ROS_nodeHandle.subscribe(sub_vel_measured_right);
    ROS_nodeHandle.advertise(pub_encoder_ticks_left);
    ROS_nodeHandle.advertise(pub_encoder_ticks_right);
}


void publish_encoders_velocities(double *vel_left, double *vel_right)
{
    vel_measured_left.data = *vel_left;
    vel_measured_right.data = *vel_right;
    pub_encoder_ticks_left.publish(&vel_measured_left);
    pub_encoder_ticks_right.publish(&vel_measured_right);
}



