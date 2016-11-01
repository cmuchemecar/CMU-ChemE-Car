#include <Data.h>
#include <SD.h>
#include <SPI.h>

#define WHEELHALLPIN 5
#define STOPHALLPIN 6
#define KILLSWITCHPIN 12
#define RELAYPIN 10

int start = 0;

int magnets = 1;
float radius = 0.068;
float circumference = 3.14 * 2 * radius;
float x = 0;
float dx = circumference / magnets;
float dt = 0;
float prevTime = 0;
float avgSpeed = 0;
long readings = 0;

int prevWheelHall = 1;
int currWheelHall = 1;

Sensor wheelHall = Data.sensor("Wheel", WHEELHALLPIN);
Sensor stopHall = Data.sensor("Stop", STOPHALLPIN);
Sensor killswitch = Data.sensor("Kill", KILLSWITCHPIN);

void setup() {
  pinMode(RELAYPIN, OUTPUT);
  digitalWrite(RELAYPIN, LOW);
  
  while(!start) {
    if (!killswitch.readDigital()) {
      start = 1;
    }
    delay(100); 
  }
  
  Data.beginSerial();
  Data.beginTimer();
  Data.debugBluetooth("Collecting data...");
  Data.startBluetooth();
  
  prevTime = Data.currentTime();
}

void loop() {
  
  if (!killswitch.readDigital() && Data.currentTime() > 1.0) {
    digitalWrite(RELAYPIN, LOW);
    Data.stopBluetooth();
    Data.freeze();
  }
  
  if (stopHall.readDigital()) {
    digitalWrite(RELAYPIN, HIGH);
  }
  else {
    digitalWrite(RELAYPIN, LOW);
    Data.debugBluetooth("--------------");
    Data.debugBluetooth("Trial time");
    Data.debugBluetooth(Data.floatToString(Data.currentTime()));
    Data.debugBluetooth("Estimated total distance");
    Data.debugBluetooth(Data.floatToString(x));
    Data.debugBluetooth("Esitmated average speed");
    Data.debugBluetooth(Data.floatToString((avgSpeed / readings)));
    Data.stopBluetooth();
    Data.freeze();
  }
  
  Data.println(wheelHall.readDigital());
  prevWheelHall = currWheelHall;
  currWheelHall = wheelHall.readDigital();
  if ((!prevWheelHall) && currWheelHall) {
    dt = Data.currentTime() - prevTime;
    prevTime = Data.currentTime();
    x += dx;
    avgSpeed += dx/dt;
    readings++;
      
    Data.debugBluetooth(Data.dataLine(
      "Distance",
      Data.floatToString(Data.currentTime()),
      Data.floatToString(x)));
      
    Data.debugBluetooth(Data.dataLine(
      "Speed",
      Data.floatToString(Data.currentTime()),
      Data.floatToString(dx/dt)));
  }

  delay(100);
}
