import serial
import time
import sys

#ser = serial.Serial('/dev/cu.AdafruitEZ-Link4e39-SPP', 9600)
#ser = serial.Serial('COM27', 9600)
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
    elif (msg.strip() != "Start" and start and not stop):
    	data = msg.split(',')
    	if data[0].strip() not in files.keys():
    		dateTime = time.strftime("%d_%m_%Y_%H_%M_%S")
    		files[data[0].strip()] = open("%s_%s.txt" % (data[0].strip(), dateTime), 'w')
        files[data[0].strip()].write('%s, %s\n' % (data[1].strip(), data[2].strip()))
    if stop:
    	for fileName in files.keys():
        	files[fileName].close()
        break

    time.sleep(0.125)
 
