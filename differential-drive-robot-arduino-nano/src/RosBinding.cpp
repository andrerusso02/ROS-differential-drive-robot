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
std_msgs::Float32 pos_measured_left;
std_msgs::Float32 pos_measured_right;

//Subscribers
ros::Subscriber<std_msgs::Float32> sub_vel_measured_left("/hardware_command/vel_l", &ROS_updateLeftWheelVelocityCommand);
ros::Subscriber<std_msgs::Float32> sub_vel_measured_right("/hardware_command/vel_r", &ROS_updateRightWheelVelocityCommand);

//Publishers
ros::Publisher pub_encoder_ticks_left("/hardware_feedback/vel_l", &vel_measured_left);
ros::Publisher pub_encoder_ticks_right("/hardware_feedback/vel_r", &vel_measured_right);
ros::Publisher pub_encoder_pos_left("/hardware_feedback/pos_l", &pos_measured_left);
ros::Publisher pub_encoder_pos_right("/hardware_feedback/pos_r", &pos_measured_right);


void ROS_init()
{
    ROS_nodeHandle.initNode();
    ROS_nodeHandle.subscribe(sub_vel_measured_left);
    ROS_nodeHandle.subscribe(sub_vel_measured_right);
    ROS_nodeHandle.advertise(pub_encoder_ticks_left);
    ROS_nodeHandle.advertise(pub_encoder_ticks_right);
    ROS_nodeHandle.advertise(pub_encoder_pos_left);
    ROS_nodeHandle.advertise(pub_encoder_pos_right);
}


void publish_hardware_feedback(double *vel_left, double *vel_right, double *pos_left, double *pos_right)
{
  vel_measured_left.data = *vel_left;
  vel_measured_right.data = *vel_right;
  pos_measured_left.data = *pos_left;
  pos_measured_right.data = *pos_right;
  pub_encoder_ticks_left.publish(&vel_measured_left);
  pub_encoder_ticks_right.publish(&vel_measured_right);
  pub_encoder_pos_left.publish(&pos_measured_left);
  pub_encoder_pos_right.publish(&pos_measured_right);
}



