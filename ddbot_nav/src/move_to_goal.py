#!/usr/bin/env python3
import rospy
import tf2_ros
import tf_conversions
from geometry_msgs.msg import Twist
from geometry_msgs.msg import PoseStamped
import math

goal = None
accepted_threshold = 0.1 # meters from goal

def callback(data):
    global goal
    goal = data
    rospy.loginfo("Goal received:\n%s", goal)


if __name__ == '__main__':

    rospy.init_node('move_to_goal', anonymous=True)
    
    tfBuffer = tf2_ros.Buffer()
    listener = tf2_ros.TransformListener(tfBuffer)

    rospy.Subscriber("/move_base_simple/goal", PoseStamped, callback)

    publisher_cmd_vel = rospy.Publisher('/mobile_base_controller/cmd_vel', Twist, queue_size=10)

    rate = rospy.Rate(10.0)

    while not rospy.is_shutdown():

        if goal is not None:

            try:
                trans_robot = tfBuffer.lookup_transform("map", rospy.get_param('/mobile_base_controller/base_frame_id'), rospy.Time())
            except (tf2_ros.LookupException, tf2_ros.ConnectivityException, tf2_ros.ExtrapolationException):
                rospy.logwarn("Error when calling lookup transform")
                rate.sleep()
                continue

            offset_x = goal.pose.position.x - trans_robot.transform.translation.x
            offset_y = goal.pose.position.y - trans_robot.transform.translation.y

            dist = math.sqrt(offset_x ** 2 + offset_y ** 2)

            print("distance = " + str(dist))
            print("x = " + str(offset_x) + " y = " + str(offset_y))

            explicit_quat = [trans_robot.transform.rotation.x, trans_robot.transform.rotation.y, trans_robot.transform.rotation.z, trans_robot.transform.rotation.w]
            roll, pitch, yaw = tf_conversions.transformations.euler_from_quaternion(explicit_quat)
            if dist > accepted_threshold:
        
                cmd_vel = Twist()
                #cmd_vel.angular.z = yaw*10
                #cmd_vel.linear.x = dist

                cmd_vel.angular.z = 4 * math.atan2(offset_y, offset_x)
                cmd_vel.linear.x = 0.5 * math.sqrt(offset_x ** 2 + offset_y ** 2)

                print("cmd_vel = " + str(cmd_vel))

                publisher_cmd_vel.publish(cmd_vel)
            else:
                goal = None

        rate.sleep()
