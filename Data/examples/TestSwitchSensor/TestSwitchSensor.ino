#include <Data.h>
#include <SD.h>
#include <SPI.h>

#define SWITCHPIN 8

SwitchSensor testSwitch = Data.switchSensor("Switch", SWITCHPIN);

void setup() {
  Data.beginSerial();
  Data.beginTimer();

  Data.println("Waiting for the switch to be turned on");
  testSwitch.waitForOn();
  Data.println("The switch has been turned on");
  Data.println("Starting control loop");
  Data.println();
}

void loop() {
  
  if (testSwitch.on()) {
    Data.println("Switch is on");
  }
  else {
    Data.println("Switch is off");
  }

  Data.display(&testSwitch);
  Data.println();

  if (Data.currentTime() > 30) {
    Data.println("30 seconds have passed");
    Data.println("Waiting for the switch to be turned off");
    Data.println();
    testSwitch.waitForOff();
    restart();
  }

  delay(1234);
}

void restart() {
  Data.println("Waiting for the switch to be turned back on");
  testSwitch.waitForOn();
  Data.println("The switch has been turned on");
  Data.println("Returning to control loop");
  Data.println();
  
  Data.beginTimer();
}

