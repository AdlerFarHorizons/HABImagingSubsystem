import serial
import time
import os
import sys
import re

def port_init():
    os.system("sudo systemctl stop serial.-getty@ttyAMA0.service")
    os.system('sudo chmod 777 /dev/ttyAMA0')
    return '-' not in os.popen('ls -l /dev/ttyAMA0').read()

port_init()
ser = serial.Serial(port='/dev/ttyAMA0',
                    baudrate=57600,
                    parity=serial.PARITY_NONE,
                    stopbits=serial.STOPBITS_ONE,
                    bytesize=serial.EIGHTBITS,
                    timeout=60)
ser.close()

counter = 0

while True:
    counter += 1
    print "counter reads {}".format(counter)
    # print "read status: {}".format(port_init())
    ser.open()
    print re.findall(r"\$(.*)\$", ser.readline())
    ser.close()
    # time.sleep(1)
