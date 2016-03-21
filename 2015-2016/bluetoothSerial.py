import serial
import time
import sys

#ser = serial.Serial('/dev/cu.AdafruitEZ-Link4e39-SPP', 9600)
ser = serial.Serial(str(sys.argv[1]), 9600)

start = False
stop = False
sensors = []
files = {}
while True:
    msg = ser.readline()
    print (msg)

    if msg.strip() == "Start":
        start = True
    if msg.strip() == "Stop":
        stop = True
    if (start and not stop):
    	data = msg.split(',')
    	if data[0] not in sensors:
    		sensors.append(data[0])
    		files[data[0]] = open("%s.txt" % data[0], 'w')
        print (msg)
        files[data[0]].write('%s, %s' % (data[1], data[2]))
    if stop:
    	for fileName in files.keys():
        	files[fileName].close()
        break

    time.sleep(0.125)
 
