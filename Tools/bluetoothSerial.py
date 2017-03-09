import serial
import time
import sys
import os

folder = os.getcwd() + "/" + str(sys.argv[2])
if not os.path.exists(folder):
    os.makedirs(folder)
print folder
#ser = serial.Serial('/dev/cu.AdafruitEZ-Link4e39-SPP', 9600)
#ser = serial.Serial('COM27', 9600)
ser = serial.Serial(str(sys.argv[1]), 9600)


start = False
stop = False
files = {}

while True:
	line = ser.readline().split(':')
	
	if (len(line) > 1 and line[0].strip().upper() == "BLUETOOTH"):

		if len(line) == 2:
			signal = line[1].strip()
			print (signal)
			
			if signal.upper() == "START":
				start = True
			elif signal.upper() == "STOP":
				stop = True
	
		elif len(line) == 3 and start:
			name = line[1].strip()
			msg = line[2].strip()
			print (name + ": " + msg)

			data = msg.split(',')
			seconds = data[0].strip()
			value = data[1].strip()
			if name not in files.keys():
				dateTime = time.strftime("%d_%m_%Y_%H_%M_%S")
				textFile = folder + "/" + ("%s_%s.txt" % (name, dateTime))
				files[name] = open(textFile, 'w')
				files[name].write('Time,Value\n')
			files[name].write('%s,%s\n' % (seconds, value))
			
	if stop:
		for fileName in files.keys():
			files[fileName].close()
		break

	#time.sleep(0.125)
 
