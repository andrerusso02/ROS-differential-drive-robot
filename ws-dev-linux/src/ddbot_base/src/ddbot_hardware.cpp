#include "ddbot_base/ddbot_hardware.h"


    DdbotHardware::DdbotHardware(ros::NodeHandle &nh)
    {
        nh = nh;
 
    }

    bool DdbotHardware::init(ros::NodeHandle &root_nh, ros::NodeHandle &robot_hw_nh)
    {
        ROS_INFO("Initializing ddbot Hardware Interface ...");

        joints_[0].name = "left_wheel";
        joints_[1].name = "right_wheel";

        for (unsigned int i = 0; i < 2; i++)
        {
            // Create a JointStateHandle for each joint and register them with the  JointStateInterface.
            hardware_interface::JointStateHandle joint_state_handle(joints_[i].name,
                                                                    &joints_[i].position, 
                                                                    &joints_[i].velocity,
                                                                    &joints_[i].effort);
            joint_state_interface_.registerHandle(joint_state_handle);

            // Create a JointHandle (read and write) for each controllable joint
            hardware_interface::JointHandle joint_handle(joint_state_handle, &joints_[i].velocity_command);
            velocity_joint_interface_.registerHandle(joint_handle);

        }

        // Register the JointStateInterface containing the read only joints
        registerInterface(&joint_state_interface_);

        // Register the JointVelocityInterface containing the read/write joints
        registerInterface(&velocity_joint_interface_);

        ROS_INFO("... Done Initializing ddbot Hardware Interface");

        return true;
    }


    void DdbotHardware::test()
    {
        ROS_INFO("Testing ddbot Hardware Interface ...");
        ROS_INFO("... Done Testing ddbot Hardware Interface");
    }