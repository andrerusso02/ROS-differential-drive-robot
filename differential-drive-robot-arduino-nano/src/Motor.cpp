#include "Arduino.h"
#include "Motor.h"
#include "Config.h"




void interrupt_callback(boolean init, int* direction_p, double* velocity_p)
{
    static unsigned long time_last_pulse = 0;
    static int* direction = NULL;
    static volatile double* velocity = NULL;
    static int iEch = 0;
    if(time_last_pulse == 0) // todo
    {
        time_last_pulse = millis();
        return;
    }
    if(init)
    {
        direction = direction_p;
        velocity = velocity_p;
    }
    else if (iEch==5)
    {
        iEch = 0;
        unsigned long time_now = millis();
        *velocity = *direction * RobotModel::wheelCircumference * 1000.0
                            / ((RobotModel::nbPulsesPerMotorRevelution/5.0) * (double)(time_now - time_last_pulse));
        time_last_pulse = time_now;
        Serial.println("Velocity: " + String(*velocity));
    }
    else
    {
        iEch++;
    }
}

void interrupt_callback_wrapper()
{
    interrupt_callback(false, NULL, NULL);
}


Motor::Motor(int enable, int dir1, int dir2, int encoder_pin)
{
    this->current_direction = 1;
    this->current_velocity = 0;

    interrupt_callback(true, &this->current_direction, &this->current_velocity);

    this->enable = enable;
    this->dir1 = dir1;
    this->dir2 = dir2;
    this->encoder_pin = encoder_pin;

    pinMode(enable, OUTPUT);
    pinMode(dir1, OUTPUT);
    pinMode(dir2, OUTPUT);
    pinMode(encoder_pin, INPUT);

    attachInterrupt(digitalPinToInterrupt(encoder_pin), &interrupt_callback_wrapper, RISING);
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
        this->current_direction = 1;
        
    }
    else if (pwm < 0)
    {
        digitalWrite(dir1, LOW);
        digitalWrite(dir2, HIGH);
        this->current_direction = -1;
    }
    else
    {
        digitalWrite(dir1, LOW);
        digitalWrite(dir2, LOW);
    }
    analogWrite(enable, abs(pwm));
}

