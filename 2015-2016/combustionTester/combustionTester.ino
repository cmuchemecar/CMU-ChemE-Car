#define PHOTOPIN A0
//input pin is the pin to attach the bleach clock sensor too
#define KILLPIN 2
//digital pin for the kill switch
#define HALLPIN A1
//analog pin for the hall effect sensor
#define THROTTLEPIN 8
//pin for throttle control
#define FANPIN 5
//pin for fan 
#define FANSWITCHPIN 4
//pin for fan switch

#include <Servo.h>

float throttleOpen = 75;
float throttleClose = 112;
float throttleInit = 75;
float throttleCurrent = throttleInit; //hold current value for throttle
Servo throttle;

void setup()
{
  Serial.begin(9600);
  Serial.println("-------------------");
  Serial.println("Begin run");

  pinMode(KILLPIN, INPUT);
  pinMode(HALLPIN, INPUT);
  pinMode(PHOTOPIN, INPUT);
  pinMode(FANPIN, OUTPUT);
  pinMode(FANSWITCHPIN, INPUT);
  throttle.attach(THROTTLEPIN);
  throttle.write(throttleInit);
  
  //test the servo
  throttle.write(throttleOpen);
  delay(1000);
  throttle.write(throttleClose);
}

void printSensor(String name, int pin, int value) {
  Serial.print(name);
  Serial.print(" (pin ");
  Serial.print(pin);
  Serial.print("): ");
  Serial.println(value);
}

void loop()
{
  int photo = analogRead(PHOTOPIN);
  int hall = analogRead(HALLPIN);
  int kill = digitalRead(KILLPIN);
  int fanSwitch = digitalRead(FANSWITCHPIN);
  printSensor("Photoresistor", PHOTOPIN, photo);
  printSensor("Hall effect", HALLPIN, hall);
  printSensor("Kill switch", KILLPIN, kill);
  printSensor("Fan switch", FANSWITCHPIN, fanSwitch);
  
  if (fanSwitch) {
    digitalWrite(FANPIN, HIGH);
  }
  else {
    digitalWrite(FANPIN, LOW);
  }
  
  Serial.println();
  delay(1000);
}
