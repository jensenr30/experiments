# This program will setup serial communication and 
import time
import serial

myPort = 'COM3'
myBaud = 19200

# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port=myPort,
    baudrate=myBaud,
	timeout=2,
	writeTimeout = 2,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_TWO,
    bytesize=serial.SEVENBITS
)

ser.isOpen()

print('Listening on Port = ' + str(myPort) + ' at ' + str(myBaud) + ' baud...')
while 1 :
	
	# check for new informatino every 10 ms
	time.sleep(0.01)
	
	out = ''
	while ser.inWaiting() > 0:		# while there are characters to grab,
		RxBytes = ser.read(1)		# get the bytes
		out += RxBytes.decode()		# convert to string

	if out != '':
		print (out, end="")