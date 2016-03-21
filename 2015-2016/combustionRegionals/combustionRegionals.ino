#define photopin A0
//photo pin is the pin to attach the luminol clock sensor too
#define killPin 1
//digital pin for the kill switch
#define hallPin 2
//analog pin for the hall effect sensor
#define throttlePin 8
//pin for throttle control


#define decreasingThreshold 5
#include <Servo.h>
unsigned long startTime;
unsigned long endTime;

float throttleOpen = 75;
float throttleClose = 112;
float throttleInit = 75;
float throttleCurrent = throttleInit;//hold current value for throttle
Servo throttle;

bool haveMoved;
int initialHallMeasurement;

int startValue;
bool hasDecreased;


void setup()
{
  Serial.begin(9600);
  Serial.println("-------------------");
  Serial.println("Begin run");

  //Get current system time
  startTime = millis();
  throttle.attach(throttlePin);
  throttle.write(throttleInit);

  pinMode(killPin, INPUT);
  pinMode(hallPin, INPUT);
  initialHallMeasurement = analogRead(hallPin);
  startValue = analogRead(photopin);
  haveMoved = false;
  hasDecreased = false;
}

void checkClock() {
  int reading = analogRead(photopin);
  Serial.println(reading);

  if((hasDecreased == false) && 
      (reading < (startValue - decreasingThreshold))) {
    hasDecreased = true;
    Serial.println("decreased");
  }
  if(hasDecreased == true) {
    if(reading > startValue - decreasingThreshold) {
      endTime = millis();
      throttle.write(throttleClose);
      Serial.print("Final input value is:");
      Serial.println(reading);
      Serial.println("\n\n\n\n\n");
      Serial.println("Car is stopped");
      unsigned long runMillis = endTime - startTime;
      Serial.print("Run time (in milliseconds: ");
      Serial.println(runMillis);
      Serial.println("-------------------");
      while (1);
    }
  }
}

void checkHall(){
  
  if(abs(analogRead(hallPin)-initialHallMeasurement)>50){
    haveMoved = true;
  }
  if (analogRead(killPin)<500){
    throttle.write(throttleClose);
    while(1); 
  }
}

void loop()
{
  if(haveMoved){
   checkClock(); 
  } 
  else{
   checkHall(); 
  }

}
