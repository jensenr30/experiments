# This is a good program to see where the bits in the serial communication is.
# This will transmit these numbers in groups:
# 1
# 2
# 4
# 8
# 16
# 32
# 64
# (goes back to 1)
# each of the numbers above is printed a bunch of times before the program moves on to the next one.
# This is allow someone with an oscilloscope to easily see:
# the 1st bit
# the 2nd-to-last bit (I can't set the last FUCKING BIT GODDAMN THIS PIECE OF SHIT GOD FUCKING DAMN IT)

# This program will setup serial communication.
import time
import serial
import random
import struct

# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port='COM3',
    baudrate=115200,
	timeout=2,
	writeTimeout = 2,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_TWO,
    bytesize=serial.SEVENBITS
)

ser.isOpen()

import string
letters = ".,? ;:!@#$%^&*()_+=-`~'\"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
import random

print ('Sending random messages with returns and newlines such as')

frequency = 30 # Hz
i = 1;
counter = 0;
while 1 :
	
	print (i)
	ser.write( struct.pack('B',i) )
	time.sleep(1/frequency)
	
	if counter > 0.5*frequency :		# if you have spent enough time on this bit,
		counter = 0						# reset your counter
		i *= 2							# move to the next bit
		if i > 255 :					# prevent i from going past the bits that a byte has.
			i = 1						# go back to bit #1
	
	counter += 1						# increment the counter