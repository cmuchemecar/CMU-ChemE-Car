#include <Data.h>
#include <SD.h>
#include <SPI.h>

//Constants
#define SDPIN 10
#define SWITCHPIN 9

//Function prototypes
void restart();

INA219CurrentSensor current = Data.ina219CurrentSensor("Current");
SwitchSensor switchSensor = Data.switchSensor("Switch", SWITCHPIN);

void setup() {
  Data.beginSerial();
  Data.beginSD(SDPIN);
  Data.beginTimer();

  Data.println("Waiting for the switch to be turned on");
  switchSensor.waitForOn();
  Data.println("The switch has been turned on");
  Data.println("Starting control loop");
  Data.println("Finished setup");
}

void loop() {
  if (switchSensor.on()) {
    Data.println("Switch on");
    Data.display(&current);
    Data.sendSD(&current);
  } else {
    Data.display(&current);
    Data.println("Switch off");
    restart();
  }
}

void restart() {
  Data.println("Waiting for the switch to be turned back on");
  switchSensor.waitForOn();
  Data.println("The switch has been turned on");
  Data.println("Returning to control loop");
  
  Data.beginTimer();
  Data.beginSD(SDPIN);
}
