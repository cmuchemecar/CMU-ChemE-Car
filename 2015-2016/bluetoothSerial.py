import serial
import time

#ser = serial.Serial('/dev/cu.AdafruitEZ-Link4e39-SPP', 9600)
ser = serial.Serial('COM27', 9600)

textFile = open("data.txt", 'w')
start = False
stop = False

while True:
    msg = ser.readline()
    print (msg)

    if msg.strip() == "Start":
        start = True
    if msg.strip() == "Stop":
        stop = True
    if (start and not stop):
        print (msg)
        textFile.write(msg)
    if stop:
        textFile.close()
        break

    time.sleep(0.125)
 
