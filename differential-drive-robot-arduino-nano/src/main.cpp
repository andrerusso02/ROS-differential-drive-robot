#include <Arduino.h>
#include "Motor.h"
#include "Config.h"

#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <PID_V1.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <ros/time.h>


Motor motorL = Motor(Pins::enableL, Pins::dir1L, Pins::dir2L, Pins::encoderL);


void printCommand(const geometry_msgs::Twist& msg)
{
    Serial.print("Linear: ");
    Serial.print(msg.linear.x);
    Serial.print(" Angular: ");
    Serial.print(msg.angular.z);
    Serial.println();
}

ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", printCommand);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // motorL.rotate(255);

}

void loop() {
  for(int i=100; i<255; i+=10)
  {
    motorL.rotate(i);
    delay(500);
    // Serial.println(i);
  }
}