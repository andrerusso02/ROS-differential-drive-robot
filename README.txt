Differential Drive Robot


Attacher / detacher la carte à WSL :
usbipd wsl list
usbipd wsl attach --busid 1-2
usbipd wsl detach --busid 1-2

Avant de lancer rosserial :
sudo chmod 666 /dev/ttyUSB0