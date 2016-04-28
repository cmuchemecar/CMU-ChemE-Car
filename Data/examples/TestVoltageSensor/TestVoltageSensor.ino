#include <Data.h>
#include <SD.h>
#include <SPI.h>

#define VOLTPIN A0

VoltageSensor volt = Data.voltageSensor("Volt", VOLTPIN, 1000, 3000);

void setup() {
  Data.beginSerial();
  Data.beginTimer();
}

void loop() {
  Data.display(&volt);
  
  delay(1234);
}
