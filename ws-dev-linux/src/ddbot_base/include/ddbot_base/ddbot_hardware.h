#ifndef DD_BOT_HARDWARE_H
#define DD_BOT_HARDWARE_H

#include "hardware_interface/joint_state_interface.h"
#include "hardware_interface/joint_command_interface.h"
#include "hardware_interface/robot_hw.h"
#include "ros/ros.h"
#include "std_msgs/Float32.h"

struct Joint
{
    std::string name;
    double position;
    double position_offset;
    double velocity;
    double effort; // unused with diff_drive_controller
    double velocity_command;

    Joint() :
    position(0), velocity(0), effort(0), velocity_command(0)
    { }
};

class DdbotHardware : public hardware_interface::RobotHW
{

    public:
        DdbotHardware(ros::NodeHandle& nh);

        void test();

        void readFromHardware();

        void writeToHardware();



    private:

        Joint joints_[2];

        ros::NodeHandle nh_;
        hardware_interface::JointStateInterface joint_state_interface_;
        hardware_interface::VelocityJointInterface velocity_joint_interface_;


        // publishers
        ros::Publisher pub_left_motor_velocity_;
        ros::Publisher pub_right_motor_velocity_;

        // subscribers
        ros::Subscriber sub_left_encoder_;
        ros::Subscriber sub_right_encoder_;

        // encoders callbacks
        void leftVelCallback(const std_msgs::Float32::ConstPtr& msg);
        void rightVelCallback(const std_msgs::Float32::ConstPtr& msg);
        void leftPosCallback(const std_msgs::Float32::ConstPtr& msg);
        void rightPosCallback(const std_msgs::Float32::ConstPtr& msg);
        // variables for encoders callbacks
        _Float32 left_encoder_vel_;
        _Float32 right_encoder_vel_;
        _Float32 left_encoder_pos_;
        _Float32 right_encoder_pos_;
};


#endif // DD_BOT_HARDWARE_H