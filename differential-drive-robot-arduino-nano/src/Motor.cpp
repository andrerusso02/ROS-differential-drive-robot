#include "Arduino.h"
#include "Motor.h"
#include "Config.h"

char current_direction = 1;

double current_velocity = 0;

void interrupt_callback()
{
    static unsigned long time_last_pulse =  millis(); // todo
    static int iEch = 0;

    if (iEch==5)
    {
        iEch = 0;
        unsigned long time_now = millis();
        // current_velocity = current_direction * RobotModel::wheelCircumference * 1000.0
        //                     / ((RobotModel::nbPulsesPerMotorRevelution/5.0) * (double)(time_now - time_last_pulse));
        current_velocity = current_direction * 5 / (double)(time_now - time_last_pulse)* 1000.0;
        if(abs(current_velocity) < 60.0)
        {
            current_velocity = 0;
        }
        time_last_pulse = time_now;
        Serial.println("Velocity: " + String(current_velocity));
    }
    else
    {
        iEch++;
    }
}


Motor::Motor(int enable, int dir1, int dir2, int encoder_pin)
{

    this->enable = enable;
    this->dir1 = dir1;
    this->dir2 = dir2;
    this->encoder_pin = encoder_pin;

    pinMode(enable, OUTPUT);
    pinMode(dir1, OUTPUT);
    pinMode(dir2, OUTPUT);
    pinMode(encoder_pin, INPUT);

    attachInterrupt(digitalPinToInterrupt(encoder_pin), &interrupt_callback, RISING);
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
        current_direction = 1;
        
    }
    else if (pwm < 0)
    {
        digitalWrite(dir1, LOW);
        digitalWrite(dir2, HIGH);
        current_direction = -1;
    }
    else
    {
        digitalWrite(dir1, LOW);
        digitalWrite(dir2, LOW);
    }
    analogWrite(enable, abs(pwm));
}

