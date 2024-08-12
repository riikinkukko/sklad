import time
import serial

arduino = serial.Serial("/dev/ttyUSB0", 115200)
time.sleep(2)
arduino.reset_input_buffer()
print(1)

while True:
	print(2)
	time.sleep(0.01)
	if arduino.in_waiting > 0:
		print(arduino.readline().decode())

arduino.close()
