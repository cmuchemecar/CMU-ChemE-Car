#include <Adafruit_MAX31855.h>
#include <SD.h>
#include <Servo.h>
#include <SPI.h>


int hallPin = 1; //analog
int throttlePin = 8; //digital
int donePin = 3; //digital for switch
int DOPin = 4;
int CSPin = 5;
int CLKPin = 6;
int sdPin = 10; 
float throttleOpen = 107;
float throttleClose = 68;
float throttleInit = 95; //random num ayy 
float throttleCurrent = throttleInit;//hold current value for throttle
boolean haveMoved = false; //haven't moved yet
int pastHallMeasurement; 
int initialHallMeasurement; 
long startTime; //when we detect movement
long onTime; //time arduino turned on
int numberMagnetDetections = 0; //when equals 6, we've done one loop of wheel
long startCurrentRotationTime; //time when we start a new loop
long timeOfRotation; //time to do one rotation of the wheel
float RPM; //current RPM
float temperature; //temp of engine

int magnetCounts = 0;

void setup(){
  Serial.begin(9600);
  pinMode(hallPin, INPUT);
  onTime = millis();
  
  pastHallMeasurement = analogRead(hallPin);  
  initialHallMeasurement = analogRead(hallPin); 
}

String floatPrint(float x){
  int intp = x;
  int fracp = (x - intp) * 1000;
  if(fracp < 0){
    fracp = -1 * fracp;
  }
  return (String(intp) + "." + String(fracp));
}


/*
wheels are 4 inch diameter
*/

/*
Check the hall effect reading
see if it's different than before
if its different, then update the counter, and if a whole loop, we're done a rotation
*/
void checkHallEffect(){
  int reading = analogRead(hallPin);
  if(reading != pastHallMeasurement){
    haveMoved = true;
    startTime = millis();
    startCurrentRotationTime = millis();
  }
  
  if(initialHallMeasurement < 5){
    if(reading < 5 && pastHallMeasurement > 80){
        Serial.println(reading);

      //so detect a magnet
      //as we're back to another new magnet
      magnetCounts++;
      Serial.println(magnetCounts);
    }
    
  }
  else{
    if(reading > 80 && pastHallMeasurement < 5){
        Serial.println(reading);
      //so now in dead zone again 
      //so passed a magnet
      magnetCounts++;
      Serial.println(magnetCounts);
     }
  }
  pastHallMeasurement = reading;
}

  
void loop(){
  checkHallEffect();   
}
