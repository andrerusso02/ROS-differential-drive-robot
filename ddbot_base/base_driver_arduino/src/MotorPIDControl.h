#ifndef PIDCONTROL_H
#define PIDCONTROL_H
#include <PID_v1.h>
#include "Motor.h"
#endif // PIDCONTROL_H

class MotorPIDControl {
    private:
        PID *pid;
        double output;
        double *cmd_vel;
        double *input_velocity;
        Motor *motor;
    public:
        MotorPIDControl(double* cmd_vel, Motor* motor, double* input_velocity);
        void spinOnce(); // updates the PID controller and sets the motor speed
};