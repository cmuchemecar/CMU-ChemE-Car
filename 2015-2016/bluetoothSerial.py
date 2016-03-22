import serial
import time
import sys

#ser = serial.Serial('/dev/cu.AdafruitEZ-Link4e39-SPP', 9600)
ser = serial.Serial(str(sys.argv[1]), 9600)

start = False
stop = False
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
    	for i in data:
    		i.strip()
    	if data[0] not in files.keys():
    		dateTime = time.strftime("%d_%m_%Y_%H:%M:%S")
    		files[data[0]] = open("%s_%s.txt" % (data[0], dateTime), 'w')
        print (msg)
        files[data[0]].write('%s, %s' % (data[1], data[2]))
    if stop:
    	for fileName in files.keys():
        	files[fileName].close()
        break

    time.sleep(0.125)
 
