import serial
import serial.tools.list_ports
import time

# This script finds the ports of the 3 USB peripherials of the robot.
# If all 3 peripherials are found they are displayed as follow:
#   Arduino_wheels /dev/tty...
#   Arduino_lidar /dev/tty...
#   Lidar_sensor /dev/tty...
# If at least one of these chips aren't found, then the message "Port(s) not found" is displayed.


WHOAMI = 0xFF # used by lidar's arduino but not wheels motors arduino
ID = 0xFE # lidar's arduino answer to WHOAMI

if __name__ == '__main__':

    arduino_wheels_found = False
    arduino_lidar_found = False
    lidar_sensor_found = False

    error = "Port(s) not found"

    response = ""

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
                    response += "Arduino_lidar " + port + "\n"
                else :
                    response = error
                    break
            else:
                if not arduino_wheels_found:
                    arduino_wheels_found = True
                    response += "Arduino_wheels " + port + "\n"
                else :
                    response = error
                    break
        elif peripherial.description == "USB Serial":
            if not lidar_sensor_found:
                lidar_sensor_found = True
                response += "Lidar_sensor " + port + "\n"
            else :
                response = error
                break
    
    if arduino_wheels_found and arduino_lidar_found and lidar_sensor_found:
        print(response[:-1], end=None) # don't print last \n
    else:
        print(error)
