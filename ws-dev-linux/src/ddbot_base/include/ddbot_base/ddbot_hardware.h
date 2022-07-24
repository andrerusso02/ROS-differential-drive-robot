#ifndef DD_BOT_HARDWARE_H
#define DD_BOT_HARDWARE_H

#include "hardware_interface/joint_state_interface.h"
#include "hardware_interface/joint_command_interface.h"
#include "hardware_interface/robot_hw.h"
#include "ros/ros.h"

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
        DdbotHardware(ros::NodeHandle &nh);

        virtual bool init(ros::NodeHandle &root_nh, ros::NodeHandle &robot_hw_nh);

        void test();



    private:

        Joint joints_[2];

        ros::NodeHandle nh_;
        hardware_interface::JointStateInterface joint_state_interface_;
        hardware_interface::VelocityJointInterface velocity_joint_interface_;
};


#endif // DD_BOT_HARDWARE_H