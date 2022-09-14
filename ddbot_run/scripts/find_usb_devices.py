#!/usr/bin/env python3

import serial
import serial.tools.list_ports
import time
import os
import rospy

# This script finds the ports of the 3 USB peripherials of the robot.
# It writes a scripts setting them as environnment variables and executes it.

WHOAMI = 0xFF # used by lidar's arduino but not wheels motors arduino
ID = 0xFE # lidar's arduino answer to WHOAMI

NS = "/peripherials_ports/"
ARDUINO_WHEELS = "arduino_wheels"
ARDUINO_LIDAR = "arduino_lidar"
LIDAR_SENSOR = "lidar_sensor"

SCRIPT_PATH = os.path.realpath(os.path.dirname(__file__)) + "/set_usb_ports.bash"

if __name__ == '__main__':

    arduino_wheels_found = False
    arduino_lidar_found = False
    lidar_sensor_found = False

    rospy.init_node('find_usb_devices', anonymous=True) # init_node needed for rospy.loginfo()

    rospy.loginfo("Searching for USB ports...")

    peripherials = serial.tools.list_ports.comports(include_links=False)
    for peripherial in peripherials:
        port = "/dev/" + peripherial.name
        if peripherial.description == "USB2.0-Serial":
            # connect to see if arduino responds to WHOAMI
            ser = serial.Serial(port, 115200, timeout=1.0)
            time.sleep(2) # wait for Arduino to reboot
            ser.write(WHOAMI.to_bytes(1, 'little'))
            res = ser.read(1)
            ser.close()
            if res == ID.to_bytes(1, 'little'): # motor Arduino found !
                if not arduino_lidar_found:
                    arduino_lidar_found = True
                    rospy.set_param(NS + ARDUINO_LIDAR, port)
                    rospy.loginfo("Set param " + NS + ARDUINO_LIDAR + "=" + port)
                else :
                    rospy.logerr("Error : Another peripherial at " + port + " matches description for " + ARDUINO_LIDAR)
            else:
                if not arduino_wheels_found:
                    arduino_wheels_found = True
                    rospy.set_param(NS + ARDUINO_WHEELS, port)
                    rospy.loginfo("Set param " + NS + ARDUINO_WHEELS + "=" + port)
                else :
                    rospy.logerr("Error : Another peripherial at " + port + " matches description for " + ARDUINO_WHEELS)
        elif peripherial.description == "USB Serial":
            if not lidar_sensor_found:
                lidar_sensor_found = True
                rospy.set_param(NS + LIDAR_SENSOR, port)
                rospy.loginfo("Set param " + NS + LIDAR_SENSOR + "=" + port)
            else :
                rospy.logerr("Error : Another peripherial at " + port + " matches description for " + LIDAR_SENSOR)
    
    rospy.signal_shutdown("Clean exit: USB search completed!")

