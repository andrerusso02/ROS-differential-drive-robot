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

  ENCODERS_update_current_velocity_measures();

  publish_hardware_feedback(&ENCODERS_global_vars::current_velocity_left,
                            &ENCODERS_global_vars::current_velocity_right,
                            &ENCODERS_global_vars::current_position_left,
                            &ENCODERS_global_vars::current_position_right);

  ROS_nodeHandle.spinOnce(); // calls the callback waiting to be called

  motorPIDControlL.spinOnce();
  motorPIDControlR.spinOnce();

  delay(100);

  
  // use this for debug
  /* 
  ENCODERS_update_current_velocity_measures();
  int val = analogRead(A0);
  float val_float = ((float)val / 1023.0 * 6.0) - 3.0;
  ROS_cmd_vel_right = val_float;
  motorPIDControlR.spinOnce();
  delay(100);
  */
  
}