// Todo: actually run

#include <Data.h>
#include <SD.h>
#include <SPI.h>

#define HALLPIN 5

HallEffectSensor hall = Data.hallEffectSensor("Hall", HALLPIN);

void setup() {
  pinMode(HALLPIN, INPUT);
  Data.beginSerial();
}

void loop() {
  
}
