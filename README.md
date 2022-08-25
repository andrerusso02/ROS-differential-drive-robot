# Differential Drive Robot


## Attacher / detacher une carte à WSL
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