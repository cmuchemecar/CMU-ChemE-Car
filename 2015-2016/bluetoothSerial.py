import serial
import time

ser = serial.Serial('/dev/cu.AdafruitEZ-Link4e39-SPP', 9600)

textFile = open("data.txt", 'w')

while True:
    start = False
    stop = False
    msg = ser.readline()
    if msg == "Start":
        start = True
    if msg == "Stop":
        stop = True
    if (start and not stop):
        print (msg)
        textFile.write(msg)
    if stop:
        textFile.close()
        break

    time.sleep(0.125)
 
