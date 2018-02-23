#include <Data.h>
#include <SD.h>
#include <SPI.h>

#define EMPTYPIN A0
#define VOLTPIN A1
#define SDPIN 10
#define SWITCHPIN 8

INA219CurrentSensor current = Data.ina219CurrentSensor("Current");

//Sensor empty = Data.sensor("Empty", EMPTYPIN);
//VoltageSensor volt = Data.voltageSensor("Volt", VOLTPIN, 1000, 3000);



void setup() {
  Data.beginSerial();
  Data.beginSD(SDPIN);
  Data.beginTimer();
  Data.println("Waiting for the switch to be turned on");
  testSwitch.waitForOn();
  Data.println("The switch has been turned on");
  Data.println("Starting control loop");
  Data.println("Finished setup");
}

void loop() {
  //Data.display(&empty);
  //Data.sendSD(&empty);
  
  //Data.display(&volt);
  //Data.sendSD(&volt);
  
  //Data.println();
    if (testSwitch.on()) {
      Data.display(&current);
      Data.sendSD(&current);
  ;
  }
  else {
    Data.display(&current);
    Data.println("Switch is off");
    testSwitch.waitForOff();
    restart();
  }

  Data.println();

  Data.println("looping");
  
  delay(1000);
}

void restart() {
  Data.println("Waiting for the switch to be turned back on");
  testSwitch.waitForOn();
  Data.println("The switch has been turned on");
  Data.println("Returning to control loop");
  Data.println();
  
  Data.beginTimer();
}
