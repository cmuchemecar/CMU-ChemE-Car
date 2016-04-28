#include <Data.h>
#include <SD.h>
#include <SPI.h>

#define EMPTYPIN A0
#define VOLTPIN A1
#define SDPIN 10

Sensor empty = Data.sensor("Empty", EMPTYPIN);
VoltageSensor volt = Data.voltageSensor("Volt", VOLTPIN, 1000, 3000);

void setup() {
  Data.beginSerial();
  Data.beginSD(SDPIN);
  Data.beginTimer();
}

void loop() {
  Data.display(&empty);
  Data.sendSD(&empty);
  
  Data.display(&volt);
  Data.sendSD(&volt);
  
  Data.println();
  
  delay(1234);
}
