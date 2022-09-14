
namespace Pins
{
    extern int enableL;
    extern int dir1L;
    extern int dir2L;
    extern int encoderL;

    extern int enableR;
    extern int dir1R;
    extern int dir2R;
    extern int encoderR;
}

namespace RobotModel
{
    extern double nbPulsesPerMotorRevelution;
    extern double maxVelocity;
}

namespace PIDConfig
{
    extern float kp;
    extern float ki;
    extern float kd;

    extern float max_output;
    extern float min_command;
}

