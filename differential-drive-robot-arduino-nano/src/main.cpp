#include <Arduino.h>
#include "Motor.h"
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


Motor motorL = Motor(Pins::enableL, Pins::dir1L, Pins::dir2L, Pins::encoderL);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // motorL.rotate(255);

}

void loop() {
  nodeHandle.spinOnce(); // calls the callback waiting to be called
  delay(10);
}