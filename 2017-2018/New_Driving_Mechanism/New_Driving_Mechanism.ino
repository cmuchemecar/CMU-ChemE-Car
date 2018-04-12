#include <Data.h>
#include <SD.h>
#include <SPI.h>

//Constants
#define SDPIN 10
#define SWITCHPIN 9

//Globals
static int trial_counter = 0;
static int NEW_TRIAL = 0;

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
  trial_counter += 1;
  NEW_TRIAL = 1;
}

void loop() {
  if (switchSensor.on()) {
    Data.println("Switch on");
    Data.display(&current);
    Data.sendSD(&current, NEW_TRIAL, trial_counter);
    if (NEW_TRIAL) {
      NEW_TRIAL = 0;
    }
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
  current.resetTimer();
  Data.beginSD(SDPIN);
  trial_counter += 1;
  NEW_TRIAL = 1;
}
