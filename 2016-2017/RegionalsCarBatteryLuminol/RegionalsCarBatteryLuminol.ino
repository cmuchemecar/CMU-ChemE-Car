#include <Data.h>
#include <SPI.h>
#include <SD.h>

#define MOTORPIN 7
#define PHOTOPIN A0
#define SWITCHPIN 10

//Value must increase by this much before being checked for decrease
int increasingThreshold = 500;
//Value must decrease by this much after starting to decrease
int decreasingThreshold = 350;
float startValue;
bool hasIncreased;

Timer clockTimer = Timer();

Series photoseries = Data.series(6);

float measurePhotoMax();
Measurement photomax = Data.measurement("Photo_Max", measurePhotoMax);

Sensor photoraw = Data.sensor("Photo_Raw", PHOTOPIN);
PhotoSensor photosensor = Data.photoSensor("Photo_Sensor", PHOTOPIN, 660000);
SwitchSensor controlswitch = Data.switchSensor("Switch_Sensor", SWITCHPIN);

MotorActuator motor = Data.motorActuator("Motor", MOTORPIN);

void setup() {
  controlswitch.waitForOn();
  
  startValue = photoraw.readValue();
  hasIncreased = false;

  Data.beginSerial();
  Data.beginTimer();
  Data.startBluetooth();

  Data.println("Starting program");
  Data.debugBluetooth("Starting program");
}

void loop() {

  if (!controlswitch.on()) {
    motor.stop();
    Data.stopBluetooth();
    restart();
  }
  
  float reading = photoraw.readValue();
  
  photoseries.update(reading);
  
  photomax.update();
  
  if((!hasIncreased) && 
     (reading > (startValue + increasingThreshold)) &&
     (photoseries.ready()) &&
     (photoseries.averageChange(3) < 0)) {
      
    startValue = reading;
    hasIncreased = true;
    
    clockTimer.reset();

    motor.start();
    
    Serial.println("############################### increased ###############################");
    Data.debugBluetooth("############################### increased ###############################");
  }
  
  if((hasIncreased) && 
     (reading < startValue - decreasingThreshold)) {
     
    motor.stop();
    
    Data.println("Reaction ended in seconds ");
    Data.println(clockTimer.duration());
    Data.println("Total max seen was ");
    Data.println(photomax.getValue());

    Data.debugBluetooth("Reaction ended in seconds ");
    Data.debugBluetooth(clockTimer.duration());
    Data.debugBluetooth("Total max seen was ");
    Data.debugBluetooth(photomax.getValue());
    Data.stopBluetooth();
      
    controlswitch.waitForOff();
    restart();
  }

  Data.display(photoraw);
  Data.display(photosensor);

  Data.sendBluetooth(&photoraw);
  Data.sendBluetooth(&photosensor);

  Data.println();
}

void restart() {
  photoseries.reset();
  photomax.reset();
  photoraw.reset();
  photosensor.reset();
  controlswitch.reset();
  motor.reset();
  
  controlswitch.waitForOn();

  startValue = photoraw.readValue();
  hasIncreased = false;

  Data.beginTimer();
  Data.startBluetooth();

  Data.println("Restarting program");
  Data.debugBluetooth("Restarting program");
}

float measurePhotoMax() {
  return max(photomax.getValue(), photoraw.readValue());
}


