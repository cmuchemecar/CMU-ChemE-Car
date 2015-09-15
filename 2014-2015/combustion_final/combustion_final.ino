#include <Adafruit_MAX31855.h>
#include <SD.h>
#include <Servo.h>
#include <SPI.h>

/****** hall effect variable initialization ******/
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
/****** end hall effect variable initialization *****/

/***** clock var initialization *****/
#define clockPin 2   // NEEDS TO BE SET PROPERLY
#define thresh 300
unsigned long clockStartTime;
unsigned long clockEndTime;
int clockPrevValue; // previous value read by photoresistor
int clockAvg; // avg of prev and current value read by photoresistor
/***** end clock var initialization *****/

/***** fan pwm var initialization *****/
#define fan_speed 128 // NEEDS TO BE SET PROPERLY
#define fanPin 7  // NEEDS TO BE SET PROPERLY
/***** end fan pwm var initialization *****/

/* function prototypes */
void setup();
void loop();
String floatPrint(float x);
void checkHallEffect();
void checkClock(); 

void setup()
{
  Serial.begin(9600);
  pinMode(hallPin, INPUT);
  onTime = millis();
  clockStartTime = millis();
  
  pastHallMeasurement = analogRead(hallPin);  
  initialHallMeasurement = analogRead(hallPin); 
}

void loop()
{
  analogWrite(fanPin, fan_speed);  // set fan speed
  
  checkHallEffect();
  checkClock();  
}

/* checks clock, displays if time > threshold */
void checkClock()
{
  
  int input = analogRead(clockPin);
  clockAvg = (input + clockPrevValue) / 2;
  
  clockPrevValue = input;
 
 if(clockAvg > thresh)
 {
   Serial.print("Input value is:");
   Serial.println(input);
 }
 else
 {
   clockEndTime = millis();
   Serial.print("Final input value is:");
   Serial.println(input);
   Serial.println("\n\n\n\n\n");
   Serial.println("Car is stopped");
   unsigned long runMillis = clockEndTime - clockStartTime;
   Serial.print("Run time (in milliseconds: ");
   Serial.println(runMillis);
   Serial.println("-------------------");
   while(1);
 }
}

String floatPrint(float x)
{
  int intp = x;
  int fracp = (x - intp) * 1000;
  if(fracp < 0)
  {
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
void checkHallEffect()
{
  int reading = analogRead(hallPin);
  if(reading != pastHallMeasurement)
  {
    haveMoved = true;
    startTime = millis();
    startCurrentRotationTime = millis();
  }
  
  if(initialHallMeasurement < 5)
  {
    if(reading < 5 && pastHallMeasurement > 80)
    {
        Serial.println(reading);

      //so detect a magnet
      //as we're back to another new magnet
      magnetCounts++;
      Serial.println(magnetCounts);
    }
    
  }
  else
  {
    if(reading > 80 && pastHallMeasurement < 5)
    {
        Serial.println(reading);
      //so now in dead zone again 
      //so passed a magnet
      magnetCounts++;
      Serial.println(magnetCounts);
     }
  }
  pastHallMeasurement = reading;
}

  



