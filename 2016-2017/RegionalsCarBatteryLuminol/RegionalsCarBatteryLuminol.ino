#include <Data.h>
#include <SPI.h>
#include <SD.h>

#define TRANSPIN 7
#define PHOTOPIN A0
#define SWITCHPIN 10

//Threshold at which we say that the value has increased
//past the starting value
#define increasingThreshold 500
#define decreasingThreshold 350
//The first reading of the luminol clock
float startValue;
//Will be set true when the value has increased past a certain value
bool hasIncreased;
//Max raw value seen
int totalMax;

Timer clockTimer = Timer();

Sensor raw_data = Data.sensor("Raw_Data", PHOTOPIN, clockTimer);
PhotoSensor photo_sensor = Data.photoSensor("Photo_Sensor", PHOTOPIN, clockTimer, 660000);
SwitchSensor control_switch = Data.switchSensor("Switch_Sensor", SWITCHPIN);

int numPoints = 6;
float points[6];
int counter = 0;
float average = 0;
bool averaging = false;

void setup() {
  control_switch.waitForOn();
  
  startValue = photo_sensor.readAnalog();
  hasIncreased = false;
  totalMax = 0;

  Data.beginSerial();
  Data.beginTimer();

  Data.startBluetooth();

  Data.debugBluetooth("Starting program");

  pinMode(TRANSPIN, OUTPUT);
}


float computeAverage(float* points, int reading) {
  float average = ((points[3] + points[4] + points[5]) / ((float) numPoints/2)) - 
    ((points[0] + points[1] + points[2]) / ((float) numPoints/2));

  int i = 0;
  for (; i < numPoints-1; i++) { 
    points[i] = points[i+1];
  }

  points[i] = reading;

  return average;
}


void loop() {

  if (!control_switch.on()) {
    analogWrite(TRANSPIN, LOW);
    Data.stopBluetooth();
    restart();
  }
  
  float reading = photo_sensor.readAnalog();

  if (!averaging) {
    if (counter < numPoints) {
      points[counter] = reading;
      counter++;
    }
    else {
      averaging = true;
    }
  }
  else {
    average = computeAverage(points, reading);
  }

  if (reading > totalMax) {
    totalMax = reading;
  }
  if((hasIncreased == false) && 
      (reading > (startValue + increasingThreshold)) &&
      average < 0) {
    startValue = reading;
    hasIncreased = true;
    clockTimer.reset();
    Serial.println("increased################################################################");
    Data.debugBluetooth("increased################################################################");
    digitalWrite(TRANSPIN, HIGH);
  }
  if((hasIncreased == true) && 
      (reading < startValue - decreasingThreshold)) {
     
    analogWrite(TRANSPIN, LOW);
    Data.println("Reaction ended in seconds ");
    Data.println((float) clockTimer.duration());
    Data.println("Total max seen was ");
    Data.println(totalMax);

    Data.debugBluetooth("Reaction ended in seconds ");
    Data.debugBluetooth(Data.floatToString(clockTimer.duration()));
    Data.debugBluetooth("Total max seen was ");
    Data.debugBluetooth(Data.floatToString(totalMax));
    Data.stopBluetooth();
      
    control_switch.waitForOff();
    restart();
  }


  Data.sendBluetooth(&raw_data);
  Data.sendBluetooth(&photo_sensor);

  Data.display(&raw_data);
  Data.display(&photo_sensor);
  Data.println();

}

void restart() {
  control_switch.waitForOn();

  startValue = photo_sensor.readAnalog();
  hasIncreased = false;
  totalMax = 0;

  Data.beginTimer();

  Data.startBluetooth();

  counter = 0;
  average = 0;
  averaging = false;
}


