#include <Arduino.h>
//#include "Motor.h"
#include "MotorPIDControl.h"
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
Motor motorL = Motor(Pins::enableL, Pins::dir1L, Pins::dir2L, Pins::encoderL);
MotorPIDControl motorPIDControlL = MotorPIDControl(&cmd_vel_left, &motorL);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  //nodeHandle.spinOnce(); // calls the callback waiting to be called
  //delay(10);

  int a = analogRead(A7);

  // convert a from 0/1023 to -0.19/-0.19
  double cmd_vel_left = (a - 512) / 512.0 * 0.19;
  Serial.print("cmd_vel: " + String(cmd_vel_left));
  motorPIDControlL.spinOnce();
  //delay(100);



  // a = map(a, 0, 1023, -255, 255);
  // Serial.println("                  Command: " + String(a));
  // motorL.rotate(a);
  // delay(500);
}