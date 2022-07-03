#include <Arduino.h>
//#include "Motor.h"
#include "MotorPIDControl.h"
#include "Encoders.h"
#include "Config.h"

#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <ros/time.h>


void printCommand(const geometry_msgs::Twist& msg)
{
    Serial.print("Linear: ");
    Serial.print(msg.linear.x);
    Serial.print(" Angular: ");
    Serial.print(msg.angular.z);
    Serial.println();
}

// ROS
ros::NodeHandle  nodeHandle;
ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", printCommand);


double cmd_vel_left = 0;
double cmd_vel_right = 0;
Motor motorL = Motor(Pins::enableL, Pins::dir1L, Pins::dir2L, &ENCODERS_global_vars::current_direction_left_motor);
Motor motorR = Motor(Pins::enableR, Pins::dir1R, Pins::dir2R, &ENCODERS_global_vars::current_direction_right_motor);
MotorPIDControl motorPIDControlL = MotorPIDControl(&cmd_vel_left, &motorL, &ENCODERS_global_vars::current_velocity_left);
MotorPIDControl motorPIDControlR = MotorPIDControl(&cmd_vel_right, &motorR, &ENCODERS_global_vars::current_velocity_right);


void test(){
  motorL.rotate(255); delay(2000);
  motorL.rotate(0);   delay(2000);
  motorL.rotate(-255);delay(2000);
  motorL.rotate(0);   delay(2000);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ENCODERS_init_callbacks(Pins::encoderL, Pins::encoderR);

}

void loop() {

  ENCODERS_update_current_velocity_measures();

  // //nodeHandle.spinOnce(); // calls the callback waiting to be called
  // //delay(10);

   int a = analogRead(A7);

  cmd_vel_left = (a - 512) / 512.0 * 0.23;
  cmd_vel_right = (a - 512) / 512.0 * 0.23;
  
  //Serial.print("commande: " + String(cmd_vel_right));
  motorPIDControlL.spinOnce();
  motorPIDControlR.spinOnce();

  delay(100);
  
  // a = map(a, 0, 1023, -255, 255);
   //Serial.println("                  Command: " + String(a));
   //motorL.rotate(a);
   //delay(500);
}