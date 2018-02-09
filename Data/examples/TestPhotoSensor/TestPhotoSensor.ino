#include <Data.h>
#include <SD.h>
#include <SPI.h>

#define PHOTOPIN A0

PhotoSensor photo = Data.photoSensor("Photo", PHOTOPIN, 660000);

void setup() {
  Data.beginSerial();
  Data.beginTimer();
}

void loop() {
  Data.display(&photo);
  
  delay(1234);
}
