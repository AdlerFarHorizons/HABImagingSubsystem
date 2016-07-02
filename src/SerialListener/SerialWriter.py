"""
Serial port writer
FOR TESTING WITH READER ONLY
"""

import serial
import datetime


# this will be configured with the proper port settings when
# connected to the OBC; currently using the generic internal port

ser = serial.Serial(port='/dev/ttyAMA0',
                    baudrate=9600,
                    parity=serial.PARITY_NONE,
                    stopbits=serial.STOPBITS_ONE,
                    bytesize=serial.EIGHTBITS,
                    timeout=1)

counter = 0

while True:
    # writes fake gps_time to internal port 
    time_str = datetime.datetime.now().strftime('%Y%m%d%_%H%M%S%f')
    ser.write(time_str)
    time.sleep(30)
    # temporary sequence cap
    if counter > 3:
        break
