#include <Data.h>
#include <SPI.h>
#include <SD.h>

#define MOTORPIN 7
#define SWITCHPIN 10
#define STOPSWITCHPIN 3

SwitchSensor controlswitch = Data.switchSensor("Switch_Sensor", SWITCHPIN);
SwitchSensor stopswitch = Data.switchSensor("Stop_Switch", STOPSWITCHPIN);

MotorActuator motor = Data.motorActuator("Motor", MOTORPIN);

void setup() {
  controlswitch.waitForOn();

  Data.beginSerial();
  Data.beginTimer();

  motor.start();

  Data.println("Starting program");
}

void loop() {

  if (!controlswitch.on()) {
    motor.stop();
    restart();
  }

  if (!stopswitch.on()) {
    motor.stop();

    Data.println("Switch was turned off");
    Data.print("Total time was ");
    Data.print(Data.currentTime());
    Data.println(" seconds");
    
    controlswitch.waitForOff();
    restart();
  }

}

void restart() {
  controlswitch.reset();
  stopswitch.reset();
  motor.reset();
  
  controlswitch.waitForOn();

  Data.beginTimer();
  
  motor.start();

  Data.println("Restarting program");
}


