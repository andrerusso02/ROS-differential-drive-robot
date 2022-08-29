#include "ddbot_base/ddbot_hardware.h"
#include "std_msgs/Float32.h"



    DdbotHardware::DdbotHardware(ros::NodeHandle& nh):nh_(nh)
    {


        ROS_INFO("Initializing ddbot Hardware Interface ..."); // todo : find why it doesn't show in rqt_console

        // velocities in rad/s

        // Setup publishers for motors
        pub_left_motor_velocity_ = nh_.advertise<std_msgs::Float32>("hardware_command/vel_l", 1); // 1 = throw away old message if new message coming
        pub_right_motor_velocity_ = nh_.advertise<std_msgs::Float32>("hardware_command/vel_r", 1);

        // Setup subscribers for encoders
        sub_left_encoder_ = nh_.subscribe("hardware_feedback/vel_l", 1, &DdbotHardware::leftVelCallback, this);
        sub_right_encoder_ = nh_.subscribe("hardware_feedback/vel_r", 1, &DdbotHardware::rightVelCallback, this);
        sub_left_encoder_ = nh_.subscribe("hardware_feedback/pos_l", 1, &DdbotHardware::leftPosCallback, this);
        sub_right_encoder_ = nh_.subscribe("hardware_feedback/pos_r", 1, &DdbotHardware::rightPosCallback, this);




        // ============ Initialize the joint state interface ============ // todo put in init()

        joints_[0].name = "wheel_left_joint";
        joints_[1].name = "wheel_right_joint";

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

    }

    void DdbotHardware::writeToHardware()
    {

        double cmd_left_velocity = joints_[0].velocity_command;
        double cmd_right_velocity = joints_[1].velocity_command;

        std_msgs::Float32 left_motor_velocity_msg;
        std_msgs::Float32 right_motor_velocity_msg;
        left_motor_velocity_msg.data = cmd_left_velocity;
        right_motor_velocity_msg.data = cmd_right_velocity;

        //ROS_INFO("Sending vels to hardware : L = %f \tR = %f", cmd_left_velocity, cmd_right_velocity);

        // Publish the commands to the motors
        pub_left_motor_velocity_.publish(left_motor_velocity_msg);
        pub_right_motor_velocity_.publish(right_motor_velocity_msg);
    }

    void DdbotHardware::readFromHardware()
    {
        joints_[0].velocity = left_encoder_vel_;
        joints_[1].velocity = right_encoder_vel_;
        joints_[0].position = left_encoder_pos_;
        joints_[1].position = right_encoder_pos_;
    }



    void DdbotHardware::leftVelCallback(const std_msgs::Float32::ConstPtr& msg)
    {
        left_encoder_vel_ = msg->data;
    }

    void DdbotHardware::rightVelCallback(const std_msgs::Float32::ConstPtr& msg)
    {
        right_encoder_vel_ = msg->data;
    }

    void DdbotHardware::leftPosCallback(const std_msgs::Float32::ConstPtr& msg)
    {
        left_encoder_pos_ = msg->data;
    }

    void DdbotHardware::rightPosCallback(const std_msgs::Float32::ConstPtr& msg)
    {
        right_encoder_pos_ = msg->data;
    }


    void DdbotHardware::test()
    {
        ROS_INFO("Testing ddbot Hardware Interface ...");
        ROS_INFO("... Done Testing ddbot Hardware Interface");
    }