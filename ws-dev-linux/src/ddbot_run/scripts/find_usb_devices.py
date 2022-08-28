import serial
import serial.tools.list_ports
import time
import os

# This script finds the ports of the 3 USB peripherials of the robot.
# It writes a scripts setting them as environnment variables and executes it.

WHOAMI = 0xFF # used by lidar's arduino but not wheels motors arduino
ID = 0xFE # lidar's arduino answer to WHOAMI

ENV_ARDUINO_WHEELS = "ROS_PORT_ARDUINO_LIDAR"
ENV_ARDUINO_LIDAR = "ROS_PORT_ARDUINO_WHEELS"
ENV_LIDAR_SENSOR = "ROS_PORT_LIDAR_SENSOR"

SCRIPT_PATH = os.path.realpath(os.path.dirname(__file__)) + "/set_usb_ports.bash"

if __name__ == '__main__':

    arduino_wheels_found = False
    arduino_lidar_found = False
    lidar_sensor_found = False

    error = "Port(s) not found"

    text_to_write = "#!/bin/sh\n"

    print("Searching for USB ports...")

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
                    text_to_write += "export " + ENV_ARDUINO_WHEELS + "=\"" + port + "\"\n"
                    print(ENV_ARDUINO_WHEELS + "=" + port)
                else :
                    print("Error : Another peripherial at " + port + " matches description for " + ENV_ARDUINO_WHEELS)
            else:
                if not arduino_wheels_found:
                    arduino_wheels_found = True
                    text_to_write += "export " + ENV_ARDUINO_LIDAR + "=\"" + port + "\"\n"
                    print(ENV_ARDUINO_LIDAR + "=" + port)
                else :
                    print("Error : Another peripherial at " + port + " matches description for " + ENV_ARDUINO_LIDAR)
        elif peripherial.description == "USB Serial":
            if not lidar_sensor_found:
                lidar_sensor_found = True
                text_to_write += "export " + ENV_LIDAR_SENSOR + "=\"" + port + "\"\n"
                print(ENV_LIDAR_SENSOR + "=" + port)
            else :
                print("Error : Another peripherial at " + port + " matches description for " + ENV_LIDAR_SENSOR)
    
    if not arduino_wheels_found and not arduino_lidar_found and not lidar_sensor_found:
        print("No peripherials were found")
    else:
        print("Writing script setting these environnment variables at " + SCRIPT_PATH)
        with open(SCRIPT_PATH, "w") as f:
            f.write(text_to_write)
            os.system("chmod +x " + SCRIPT_PATH)
        print("Please run :\n\n\t source " + SCRIPT_PATH + "\n")

