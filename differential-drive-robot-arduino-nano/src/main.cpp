#include <Arduino.h>
//#include "Motor.h"
#include "MotorPIDControl.h"
#include "Encoders.h"
#include "Config.h"

#include "RosBinding.h"


Motor motorL = Motor(Pins::enableL, Pins::dir1L, Pins::dir2L, &ENCODERS_global_vars::current_direction_left_motor);
Motor motorR = Motor(Pins::enableR, Pins::dir1R, Pins::dir2R, &ENCODERS_global_vars::current_direction_right_motor);
MotorPIDControl motorPIDControlL = MotorPIDControl(&ROS_cmd_vel_left, &motorL, &ENCODERS_global_vars::current_velocity_left);
MotorPIDControl motorPIDControlR = MotorPIDControl(&ROS_cmd_vel_right, &motorR, &ENCODERS_global_vars::current_velocity_right);


void setup() {
  // put your setup code here, to run once:
  ENCODERS_init_callbacks(Pins::encoderL, Pins::encoderR);
  ROS_init();

}

void loop() {

  // update tick count for ROS
  publish_encoders_ticks(&ENCODERS_global_vars::nb_ticks_encoder_l, &ENCODERS_global_vars::nb_ticks_encoder_r);

  ROS_nodeHandle.spinOnce(); // calls the callback waiting to be called

  motorPIDControlL.spinOnce();
  motorPIDControlR.spinOnce();

  delay(100);
  
}