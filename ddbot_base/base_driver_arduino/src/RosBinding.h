#include <ros.h>
#include <std_msgs/Int16.h>

extern double ROS_cmd_vel_left;
extern double ROS_cmd_vel_right;
extern ros::NodeHandle ROS_nodeHandle;
extern std_msgs::Int16 ROS_cnt_ticks_left;
extern std_msgs::Int16 ROS_cnt_ticks_right;

void ROS_init();

void publish_hardware_feedback(double *vel_left, double *vel_right, double *pos_left, double *pos_right);
