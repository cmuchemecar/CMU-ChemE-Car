#include <Data.h>

#define EMPTYPIN A0
#define VOLTPIN A1

Sensor empty = Data.sensor("Empty", EMPTYPIN);
VoltageSensor volt = Data.voltageSensor("Volt", VOLTPIN, 1000, 3000);

void setup() {
  Data.beginSerial();
  Data.beginTimer();
}

void loop() {
  Data.display(empty);
  Data.display(volt);
  empty.digitalPrintln();
  empty.analogPrintln();
  Data.println();
  delay(1234);
}

