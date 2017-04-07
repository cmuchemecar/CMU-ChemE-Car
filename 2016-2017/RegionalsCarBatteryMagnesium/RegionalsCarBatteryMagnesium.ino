#include <Data.h>
#include <SPI.h>
#include <SD.h>

#define TRANSPIN 7
#define SWITCHPIN 10
#define STOPSWITCHPIN 3

SwitchSensor control_switch = Data.switchSensor("Switch_Sensor", SWITCHPIN);
SwitchSensor stop_switch = Data.switchSensor("Stop_Switch", STOPSWITCHPIN);

void setup() {
  control_switch.waitForOn();

  Data.beginSerial();
  Data.beginTimer();

  pinMode(TRANSPIN, OUTPUT);
  digitalWrite(TRANSPIN, HIGH);

  Data.println("Starting");
}

void loop() {

  if (!control_switch.on()) {
    digitalWrite(TRANSPIN, LOW);
    restart();
  }

  else if(!stop_switch.on()) {
    digitalWrite(TRANSPIN, LOW);

    Data.println("Switch was turned off");
    Data.print("Total time was ");
    Data.print(Data.currentTime());
    Data.println(" seconds");
    
    control_switch.waitForOff();
    restart();
  }

}

void restart() {
  control_switch.waitForOn();

  Data.println("Restarting");

  Data.beginTimer();
  digitalWrite(TRANSPIN, HIGH);
}


