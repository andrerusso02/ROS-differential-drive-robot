#include "Arduino.h"
#include "Motor.h"
#include "Config.h"



Motor::Motor(int enable, int dir1, int dir2, int* current_direction)
{

    this->enable = enable;
    this->dir1 = dir1;
    this->dir2 = dir2;
    this->current_direction = current_direction;

    pinMode(enable, OUTPUT);
    pinMode(dir1, OUTPUT);
    pinMode(dir2, OUTPUT);
    

}

void Motor::rotate(int pwm)
{
    if (pwm > 255)
        pwm = 255;
    if (pwm < -255)
        pwm = -255;
    if (pwm > 0)
    {
        digitalWrite(dir1, HIGH);
        digitalWrite(dir2, LOW);
        analogWrite(enable, abs(pwm));
        *current_direction = 1;
    }
    else if (pwm < 0)
    {
        digitalWrite(dir1, LOW);
        digitalWrite(dir2, HIGH);
        analogWrite(enable, abs(pwm));
        *current_direction = -1;
    }
    else
    {
        digitalWrite(dir1, LOW);
        digitalWrite(dir2, LOW);
        analogWrite(enable, LOW);
    }
    
}

