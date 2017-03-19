#include <Data.h>
#include <SD.h>
#include <SPI.h>

#define WHEELPIN 2

WheelSensor wheel = Data.wheelSensor("Wheel", WHEELPIN, 2.0, 4);

void setup() {
  Data.beginSerial();
  Data.beginTimer();
}

void loop() {
  
  if (wheel.passed()) {
    Data.println("Wheel has started moving");
    Data.print("Wheel has moved ");
    Data.print(wheel.ticks());
    Data.print(" tick(s), which is ");
    Data.print(wheel.revolutions());
    Data.print(" revolution(s) and ");
    Data.print(wheel.readValue());
    Data.println(" total distance");
  }
  else {
    Data.println("Wheel has not started moving");
  }

  Data.display(&wheel);
  Data.println();

  if (wheel.readValue() > 100) {
    Data.println("Distance has exceeded 100");
    Data.println("Resetting the wheel");
    Data.println();
    wheel.reset();
  }
  
  delay(1234);
}

