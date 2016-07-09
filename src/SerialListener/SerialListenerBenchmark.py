import serial
import time
import os
import sys
import re

def execute_shutter_sequence(gps_time):
    command = '/home/pi/flycapture_2.8/bin/NitesatSequence ' + str(gps_time)
    exit_code = os.system(command)
    if exit_code != 0:
        print 'NitesatSequence failed with exit code ' + str(exit_code)
        sys.exit(exit_code)

counter = 0

while True:
    # gps_time string will be read across serial
    input_gps_time = 'benchmark_test'
    execute_shutter_sequence(input_gps_time)
    time.sleep(24)
    counter += 1
        
