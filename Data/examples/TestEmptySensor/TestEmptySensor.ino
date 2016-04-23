#include <Data.h>

#define EMPTYPIN A0

Sensor empty = Data.sensor("Empty", EMPTYPIN);

void setup() {
  Data.beginSerial();
  Data.beginTimer();
}

void loop() {
  Data.display(empty);
  Data.print("Value: ");
  empty.println();
  Data.print("Analog: ");
  Data.println(empty.readAnalog());
  Data.print("Digital: ");
  Data.println(empty.readDigital());
  Data.println();
  
  delay(1234);
}
