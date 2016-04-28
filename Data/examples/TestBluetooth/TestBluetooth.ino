#include <Data.h>
#include <SD.h>
#include <SPI.h>

#define EMPTYPIN A0
#define VOLTPIN A1

Sensor empty = Data.sensor("Empty", EMPTYPIN);
VoltageSensor volt = Data.voltageSensor("Volt", VOLTPIN, 1000, 3000);

void setup() {
  Data.beginSerial();
  Data.beginTimer();
  Data.debugBluetooth("Collecting data...");
  Data.startBluetooth();
}

void loop() {
  
  Data.sendBluetooth(&empty);
  Data.sendBluetooth(&volt);
  
  if (Data.currentTime() > 10) {
    Data.stopBluetooth();
    Data.freeze();
  }
  
  delay(1234);
}
