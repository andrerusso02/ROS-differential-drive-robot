#include "hardware_interface/joint_state_interface.h"
#include "hardware_interface/joint_command_interface.h"
#include "hardware_interface/robot_hw.h"
#include "ros/ros.h"

class DdbotHardware : public hardware_interface::RobotHW
{
    //public:



    private:
        ros::NodeHandle nh_;
        hardware_interface::JointStateInterface joint_state_interface_;
        hardware_interface::VelocityJointInterface velocity_joint_interface_;
};