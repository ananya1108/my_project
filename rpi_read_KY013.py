import serial
import time

arduino=serial.Serial('/dev/ttyACM0',9600)

while True:
	data=(arduino.readline().decode().strip())
	print(data)