# This program will setup serial communication and 
import time
import serial

# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port='COM3',
    baudrate=600,
	timeout=2,
	writeTimeout = 2,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_TWO,
    bytesize=serial.SEVENBITS
)

ser.isOpen()

print ('Enter your commands below.\r\nInsert "exit" to leave the application.')

while 1 :
	# get keyboard input
	
	text = input()
	if text =='exit':
		ser.close()
		exit()
	else:
	
		# send the character to the device
		# (note that I happend a \r\n carriage return and line feed to the characters - this is requested by my device)
		text = text + '\r\n'
		ser.write(text.encode())
		# let's wait one second before reading output (let's give device time to answer)
		time.sleep(1)
		
		out = ''
		while ser.inWaiting() > 0:		# while there are characters to grab,
			RxBytes = ser.read(1)		# get the bytes
			out += RxBytes.decode()		# convert to string

		if out != '':
			print (out)