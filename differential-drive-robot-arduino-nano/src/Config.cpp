#include "Config.h"

namespace Pins
{
    int enableL = 10;
    int dir1L = 11;
    int dir2L = 12;
    int encoderL = 2;
}

namespace RobotModel
{
    double nbPulsesPerMotorRevelution = 200;
    double wheelCircumference = 0.3192; // m (diameter = 2inch = 5.08cm)
}

namespace PIDConfig
{
    float kp = 1.0;
    float ki = 5.0;
    float kd = 0.00;

    float max_output = 0.3;
    float min_command = 0.06;
}

    // 2e meilleur
    // float kp = 2.0;
    // float ki = 5.0;
    // float kd = 0.00;

    // float kp = 2.0;
    // float ki = 5.0;
    // float kd = 0.05;

    // float kp = 2.0;
    // float ki = 5.0;
    // float kd = 0.0;


    // float kp = 1.0;
    // float ki = 1.0;
    // float kd = 0.0;