# This program will setup serial communication and 
import time
import serial
import random

# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port='COM3',
    baudrate=9600,
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

while 1 :
	# determine the string to send
	
	#char = random.choice(letters)
	#char = 'U'
	numb = random.randrange(0,128)
	char = chr(numb)
	
	# print the character(s)
	
	print (char)
	ser.write( char.encode() )
	time.sleep(1/30)
	