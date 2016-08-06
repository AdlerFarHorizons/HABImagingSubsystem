Setup on Raspbery Pi 2 model B:

Debian "jessie" standard Pi distro on a 64GB Class 10 SD card

Kernel re-compiled to increase usb buffer size from 32Mb to 1000Mb to allow capture of full resolution/color images from the Point Grey Grasshopper3 camera

SerialListener.py requires the GPIO serial pins to be enabled as a simple uart without login capability.

  sudo raspi-config

    Advanced Options:Serial:No to disable the login shell

  sudo vi /boot/config.txt

    change last line to "enable_uart=1" without quotes

The script is started on power up through a line at the end of .bashrc which will be executed upon login when the bare Pi is powered up, but note that it will also be started whenever a terminal is opened when interacting with the unit through the desktop:

  sudo python /home/pi/HABImagingSubsystem/src/SerialListener/SerialListener.py &

If in interactive mode with the Pi, you can enter the following command upon opening a terminal session to kill the running imaging program(s):

  sudo kill $(pgrep -f python\ /home)
