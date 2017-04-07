#include <Data.h>
#include <SPI.h>
#include <SD.h>

#define LEDPIN 13

Actuator led = Data.actuator("Led", LEDPIN);

void setup() {
  Data.beginSerial();
  Data.beginTimer();
}

void loop() {
  led.writeDigital(LOW);
  Data.display(&led);

  delay(1234);

  led.writeDigital(HIGH);
  Data.display(&led);
  
  delay(1234);
}
