#include <Servo.h>
Servo Motor;

const int MF = 20;  // angle that moves motor forward
const int MB = 138; // angle that moves motor backward
const int MS = 91; // angle that stops the motor


int SWITCHPIN = 7;
int MOTORPIN = 5;

int inject;

void setup()
{
  Serial.begin(9600);
  Motor.attach(MOTORPIN);
  pinMode(SWITCHPIN, INPUT);
  inject = 1;
}

void loop()
{
  int pinOpen = digitalRead(SWITCHPIN);
  Serial.println(pinOpen);

  if (inject) {
    if (pinOpen) {
      Motor.write(MF); // move forward
    }
    else {
      Motor.write(MS); // stop motor
      delay(1000);
      Motor.write(MB); // move backward
      delay(5000);
      Motor.write(MS); // stop motor
      delay(1000);
      inject = 0;
    }
  }

  delay(100);
}


