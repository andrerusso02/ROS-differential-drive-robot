#include "Config.h"

namespace Pins
{
    int enableR = 11;
    int dir1R = 9;
    int dir2R = 10;
    int encoderR = 2;

    int enableL = 6;
    int dir1L = 8;
    int dir2L = 7;
    int encoderL = 3;
}

namespace RobotModel
{
    double nbPulsesPerMotorRevelution = 220;
}

namespace PIDConfig
{
    float kp = 1.0;
    float ki = 5.0;
    float kd = 0.00;

    float max_output = 6.0; // (on peut dire rad/s mais cela sert juste à avoir une sortie de pid à l'échelle de l'entrée) 
    float min_command = 0.30;
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