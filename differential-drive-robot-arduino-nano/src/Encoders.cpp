#include "Encoders.h"
#include "Config.h"

#include <Arduino.h>
#include <util/atomic.h>


namespace ENCODERS_global_vars
{
    int current_direction_left_motor = 1;
    int current_direction_right_motor = 1;

    double current_velocity_left = 0;
    double current_velocity_right = 0;
}

volatile long nb_ticks_encoder_left_since_update = 0;
volatile long nb_ticks_encoder_right_since_update = 0;



void ENCODERS_left_interrupt_callback()
{
    nb_ticks_encoder_left_since_update = nb_ticks_encoder_left_since_update + ENCODERS_global_vars::current_direction_left_motor;
}

void ENCODERS_right_interrupt_callback()
{
    nb_ticks_encoder_right_since_update = nb_ticks_encoder_right_since_update + ENCODERS_global_vars::current_direction_right_motor;
}

void ENCODERS_init_callbacks(int pinL, int pinR)
{
    pinMode(pinL, INPUT);
    pinMode(pinR, INPUT);
    attachInterrupt(digitalPinToInterrupt(pinL), &ENCODERS_left_interrupt_callback, RISING);
    attachInterrupt(digitalPinToInterrupt(pinR), &ENCODERS_right_interrupt_callback, RISING);
}

void ENCODERS_update_current_velocity_measures()
{
    static unsigned long t_last_call = 0;
    if(t_last_call == 0)
    {
        t_last_call = millis();
        return;
    }
    unsigned long t_now = millis();
    double dt = (double)(t_now - t_last_call) / 1000.0;
    t_last_call = t_now;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        ENCODERS_global_vars::current_velocity_left = (nb_ticks_encoder_left_since_update / dt) * RobotModel::wheelCircumference
             / RobotModel::nbPulsesPerMotorRevelution;
        ENCODERS_global_vars::current_velocity_right = (nb_ticks_encoder_right_since_update / dt) * RobotModel::wheelCircumference
            / RobotModel::nbPulsesPerMotorRevelution;
        nb_ticks_encoder_left_since_update = 0;
        nb_ticks_encoder_right_since_update = 0;
    }

}
