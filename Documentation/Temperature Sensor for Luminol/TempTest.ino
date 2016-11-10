#include <Data.h>
#include <SPI.h>
#include <SD.h>

//TMP36 Pin
#define tempPin A5
//Analog pin of photoresistor
#define photoresistor A0

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

//SD Setup
#define SDPIN 10
#define MODE_C 0
#define MODE_F 1


TemperatureSensor temp_sensor = Data.temperatureSensor("Temperature_Sensor_1", tempPin, MODE_C);

void setup() {
  pinMode(tempPin, INPUT);
  Serial.begin(9600);
  startTime = millis();
  startValue = analogRead(photoresistor);
  hasIncreased = false;

  //Set Up SD Card
  Data.beginSerial();
  Data.beginSD(SDPIN);
  Data.beginTimer();

  
}

void loop() {
  int reading = analogRead(photoresistor);
  Serial.println(reading);
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

  //Temperature Reading
  Data.display(&temp_sensor);
  Data.sendSD(&temp_sensor);
}

