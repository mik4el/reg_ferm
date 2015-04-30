#!/usr/bin/python

'''
by Ben Kenney - July 2012
This program reads data coming from the serial port and saves that data to a text file. It expects data in the format:
"photocell_reading,thermistor_reading"

It assumes that the Arduino shows up in /dev/ttyACM0 on the Raspberry Pi which should happen if you're using Debian.
'''


import serial
from time import strftime
from datetime import datetime, time

ser = serial.Serial('/dev/ttyACM0',9600)

startTime = datetime.now()
try:
	while 1:
		line=ser.readline().rstrip()
		setpoint, T_fermentor, T_isolering, T_kylvatten, T_luft =line.split(",")
		now = datetime.now()
		elapsedTime = now-startTime
		elapsedSeconds = (elapsedTime.microseconds+(elapsedTime.days*24*3600+elapsedTime.seconds)*10**6)/10**6
		print("%s,%s,%s,%s,%s,%s,%s"%(now.strftime("%Y-%m-%d %H:%M:%S"),elapsedSeconds,setpoint,T_fermentor, T_isolering, T_kylvatten, T_luft))
		f=open('tempLog.dat','a')
		print >>f,("%s,%s,%s,%s,%s,%s,%s"%(now.strftime("%Y-%m-%d %H:%M:%S"),elapsedSeconds,setpoint,T_fermentor, T_isolering, T_kylvatten, T_luft))
		f.close()
except KeyboardInterrupt:
	print "\ndone"


while not connected:
        serin = ser.read()
        connected = true
