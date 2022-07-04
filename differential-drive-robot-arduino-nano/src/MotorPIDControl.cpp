#include "Config.h"
#include "MotorPIDControl.h"

#include <Arduino.h>
#include <PID_V1.h>


MotorPIDControl::MotorPIDControl(double* cmd_vel, Motor* motor, double* input_velocity)
{
    this->motor = motor;
    this->output = 0;
    this->cmd_vel = cmd_vel;
    this->input_velocity = input_velocity;
    this->pid = new PID(input_velocity, &output, cmd_vel, PIDConfig::kp, PIDConfig::ki, PIDConfig::kd, DIRECT);
    pid->SetMode(AUTOMATIC); // turn on PID
    pid->SetOutputLimits(-PIDConfig::max_output, PIDConfig::max_output); // set the output limits


}

void MotorPIDControl::spinOnce()
{
    if(abs(*cmd_vel) < PIDConfig::min_command)
    {
        pid->SetMode(MANUAL);
        output = 0;
    }else
    {
         pid->SetMode(AUTOMATIC);   
    }
    this->pid->Compute();
    int pwm = output / RobotModel::maxVelocity * 255.0;
    this->motor->rotate(pwm);
}