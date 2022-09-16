# Differential Drive Robot

## rosserial_arduino error workaround
Check https://answers.ros.org/question/361930/rosserial-arduino-compilation-error-no-cstring/?answer=382803#post-id-382803 (Yash Sahu answer)


## Attach / detach a USB peripherial to WSL
```usbipd wsl list```
```usbipd wsl attach --busid 1-2```
```usbipd wsl detach --busid 1-2```

And before using it:
```sudo chmod 666 /dev/ttyUSB0```

## Network configuration for Raspberry Pi + workstation

### Raspberry Pi's hostname : ddrobot
SSH  : ```ssh ubuntu@ddrobot```
Change hostname : https://www.pragmaticlinux.com/2021/05/how-to-change-the-hostname-of-your-raspberry-pi/

### Run this on each machine to share roscore
```export ROS_MASTER_URI=http://ddbot:11311```

## Before launching robot nodes :

Run ```$(rospack find ddbot_run)/scripts/find_usb_devices.py```

And source ```$(rospack find ddbot_run)/scripts/set_usb_ports.bash```

Adding this to .bashrc may be convenient : 

```test -f $(rospack find ddbot_run)/scripts/set_usb_ports.bash  && source $(rospack find ddbot_run)/scripts/set_usb_ports.bash```

## Setup SSH RSA keys to use launch files to run nodes on distant robot
https://www.digitalocean.com/community/tutorials/how-to-set-up-ssh-keys-on-ubuntu-1804-fr

And place commands to init ROS in a file ```~/setup_ros.bash``` instead of ```~/.bashrc```