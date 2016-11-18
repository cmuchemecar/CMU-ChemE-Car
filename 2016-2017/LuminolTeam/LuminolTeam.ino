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
#define increasingThreshold 5


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

void setup() {
  startTime = millis();
  startValue = analogRead(PHOTOPIN);
  hasIncreased = false;

  //Set Up SD Card
  Data.beginSerial();
  Data.beginSD(SDPIN);
  Data.beginTimer();
}

void loop() {
  int reading = analogRead(PHOTOPIN);

  if (reading > totalMax) {
    totalMax = reading;
  }
  if((hasIncreased == false) && 
      (reading > (startValue + increasingThreshold))) {
    hasIncreased = true;
    Serial.println("increased");
  }
  if(hasIncreased == true) {
    if(reading < startValue + increasingThreshold) {
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
}

