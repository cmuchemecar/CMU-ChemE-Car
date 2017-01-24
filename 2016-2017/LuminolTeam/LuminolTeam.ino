#include <Data.h>
#include <SPI.h>
#include <SD.h>

//TMP36 Pin
#define TEMPPIN A5
//Analog pin of photoresistor
#define PHOTOPIN A0
//SD Setup
#define SDPIN 10

//Threshold at which we say that the value has increased
//past the starting value
#define increasingThreshold 500
#define decreasingThreshold 350

//The first reading of the luminol clock
int startValue;

//Will be set true when the value has increased past
//a certain value
bool hasIncreased;

//Start time
unsigned long startTime;

int totalMax = 0;

Sensor raw_data = Data.sensor("Raw_Data", PHOTOPIN);
PhotoSensor photo_sensor = Data.photoSensor("Photo_Sensor", PHOTOPIN, 660000);
TemperatureSensor temp_sensor = Data.temperatureSensor("Temperature_Sensor", TEMPPIN, MODE_C);

int numPoints = 6;
float points[6];
int counter = 0;
float average = 0;
bool averaging = false;

void setup() {
  startValue = analogRead(PHOTOPIN);
  hasIncreased = false;

  //Set Up SD Card
  Data.beginSerial();
  Data.beginSD(SDPIN);
  Data.beginTimer();
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
  
  int reading = analogRead(PHOTOPIN);

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
    startValue = analogRead(PHOTOPIN);
    hasIncreased = true;
    startTime = millis();
    Serial.println("increased################################################################");
  }
  if(hasIncreased == true) {
    if(reading < startValue - decreasingThreshold) {
      Serial.println("Reaction ended in milliseconds: ");
      Serial.println(millis()-startTime);
      Serial.println("Total max seen was: ");
      Serial.println(totalMax);
      while(1){}
    }
  }

  Data.sendSD(&raw_data);
  Data.sendSD(&photo_sensor);
  Data.sendSD(&temp_sensor);
  Data.display(&raw_data);
  Data.display(&photo_sensor);
  Data.display(&temp_sensor);
  Data.println();

}


