#ifndef CONGIG_H

namespace Pins
{
    extern int enableL;
    extern int dir1L;
    extern int dir2L;
    extern int encoderL;
}

namespace RobotModel
{
    extern double nbPulsesPerMotorRevelution;
    extern double wheelCircumference;
}

namespace PIDConfig
{
    extern float kp;
    extern float ki;
    extern float kd;
}
#endif // CONFIG_H
