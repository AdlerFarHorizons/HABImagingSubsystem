import serial
import time
import os
import sys
import re

# this will be configured with the proper port settings when
# connected to the OBC; currently using the generic internal port

def port_init():
    # disables a port-hogging service that crashes pyserial
    os.system("sudo systemctl stop serial.-getty@ttyAMA0.service")
    # change read access on port
    os.system("sudo chmod 777 /dev/ttyAMA0")

port_init()

ser = serial.Serial(port='/dev/ttyAMA0',
                    baudrate=57600,
                    parity=serial.PARITY_NONE,
                    stopbits=serial.STOPBITS_ONE,
                    bytesize=serial.EIGHTBITS,
                    timeout=45)

def execute_shutter_sequence(gps_time):
    command = '/home/pi/flycapture_2.8/bin/NitesatSequence ' + str(gps_time).replace('\0', '')
    exit_code = os.system(command)
    if exit_code != 0:
        print 'NitesatSequence failed with exit code ' + str(exit_code)
        sys.exit(exit_code)

counter = 0

while True:
    # gps_time string will be read across serial
    input_gps_time = ser.readline()
    # grab contents between signal start and end
    if re.findall(r"\$(.*)\$", input_gps_time):
        target_date = re.findall(r"\$(.*)$", input_gps_time)[0]
        execute_shutter_sequence(target_date)
        #os.system( "touch " + target_date + ".tmp" ) #Testing without camera
        counter += 1
        input_gps_time = ''
    # temporary sequence cap DELETE BEFORE LAUNCH
    #if counter > 5:
    #    ser.close()
    #    break
        
