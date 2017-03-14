#include <Data.h>
#include <SD.h>
#include <SPI.h>

#define HALLPIN 2

HallEffectSensor hall = Data.hallEffectSensor("Hall", HALLPIN);

void setup() {
  Data.beginSerial();
  Data.beginTimer();
}

void loop() {

  hall.readValue();
  
  if (hall.touched()) {
    Data.println("Sensor has been touched");
  }
  else {
    Data.println("Sensor has not been touched");
  }

  if (hall.on()) {
    Data.println("Sensor is currently on");
  }
  else {
    Data.println("Sensor is currently off");
  }

  Data.display(&hall);

  Data.println();
  delay(1234);
}





