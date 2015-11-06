#define inputpin 0
//input pin is the pin to attach the bleach clock sensor too
#define killPin 1
//digital pin for the kill switch
#define hallPin 2
//analog pin for the hall effect sensor
#define throttlePin 8
//pin for throttle control


#define thresh 300
#include <Servo.h>
unsigned long startTime;
unsigned long endTime;

//This will stop the car if the average of the currently read value
//and the previously read value is past the threshold point

//Previous value read by the photoresistor
int prevValue;
//Average of the previous value and the current value
//read by the photoresistor
int avg;
float throttleOpen = 75;
float throttleClose = 112;
float throttleInit = 75;
float throttleCurrent = throttleInit;//hold current value for throttle
Servo throttle;

boolean haveMoved;
int initialHallMeasurement;


void setup()
{
  Serial.begin(9600);
  Serial.println("-------------------");
  Serial.println("Begin run");

  prevValue = thresh;

  //Get current system time
  startTime = millis();
  throttle.attach(throttlePin);
  throttle.write(throttleInit);

  pinMode(killPin, INPUT);
  pinMode(hallPin, INPUT);
  initialHallMeasurement = analogRead(hallPin);
  haveMoved = false;
}

void checkClock() {
  int input = analogRead(inputpin);

  avg = (input + prevValue) / 2;

  if (avg > thresh && (analogRead(killPin) > 500))
  {
    Serial.print("Input value is:");
    Serial.println(input);
  }
  else
  {
    endTime = millis();
    throttle.write(throttleClose);
    Serial.print("Final input value is:");
    Serial.println(input);
    Serial.println("\n\n\n\n\n");
    Serial.println("Car is stopped");
    unsigned long runMillis = endTime - startTime;
    Serial.print("Run time (in milliseconds: ");
    Serial.println(runMillis);
    Serial.println("-------------------");
    while (1);
  }

  prevValue = input;
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
