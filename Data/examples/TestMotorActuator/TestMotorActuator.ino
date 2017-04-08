#include <Data.h>
#include <SPI.h>
#include <SD.h>

#define MOTORPIN 10

MotorActuator motor = Data.motorActuator("Motor", MOTORPIN);

void setup() {
  Data.beginSerial();
  Data.beginTimer();
}

void loop() {
  motor.start();
  Data.display(&motor);

  delay(1234);

  motor.stop();
  Data.display(&motor);
  
  delay(1234);
}
