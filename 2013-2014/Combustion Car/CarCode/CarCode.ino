#include<Servo.h>
#include<SD.h>

int hall = 10;
int done = 7;
int clockpin = 3;
int throtpin = 8;
boolean hstate = true;
boolean stopped = false;
long count = 0; // total number of rotations before car stops
float closed = 45;
float minAngle = 94;
float maxAngle = 104;
int clockCutoff = 900; //initial value, is changed later
float RPM = 0;
long target_speed = 190;
int RPMLimit = 300; // max reasonable RPM. ignore higher values (bumping car)
int clockSensitivity = 25; //code now reads initial clock value and waits for changre greater than sensitivity

float throttle_init = 96;
float throttle_movement_init = 98; //value to change to once movement starts
boolean haveMoved;


double inc_rate = 0.5;
double dec_rate = 0.5;
int sensitivity = 5;
double circum = 31.9;
double angle;
long startTime;
long endTime;

Servo throttle;
char filename[] = "datafile.txt";
File data;

void setup()
{
  throttle.attach(throtpin); 
  Serial.begin(9600);
  throttle.write(throttle_init);
  angle = throttle_init;
  haveMoved = false;
  pinMode(hall, INPUT);
  pinMode(done, INPUT);
  pinMode(clockpin, INPUT);
  pinMode(10, OUTPUT); //for SD card
  SD.begin(10);
  data = SD.open(filename, FILE_WRITE);
  data.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~new run time~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  data.println("angle, RPM, number of rotations, time in milliseconds, clock reading");
  data.close();
}

String floatPrint(float x){
  int intp = x;
  int fracp = (x - intp) * 1000;
  if(fracp < 0){
    fracp = -1 * fracp;
  }
  return (String(intp) + "." + String(fracp));
}

void SDWriteLn(){
    data = SD.open(filename, FILE_WRITE);
    data.println(floatPrint(angle) + "," + floatPrint(RPM)  + "," + 
                        String(count, DEC) + "," + millis()+", "+floatPrint(analogRead(clockpin)));
    data.close();
}

boolean clockdone()
{
  if (analogRead(clockpin)<=clockCutoff)
  {
    delay(50);
    if (analogRead(clockpin)<=clockCutoff)
    {
      return true;
    }
    else return false;
  }
  else return false;
}


void checkEndAndRecord()
{
  if (haveMoved && (digitalRead(done)==HIGH || clockdone()))//end switch flipped or iodine end
  {
    long distance = count*circum / 2;
    data = SD.open(filename, FILE_WRITE);
    data.println("distance traveled = " + String(distance, DEC));
    int reading = analogRead(clockpin);
    data.println("clock = " + String(reading, DEC));
    data.println("clock cutoff = " + String(clockCutoff, DEC));
    data.close();
    throttle.write(closed);
    stopped = true;
    digitalWrite(done, HIGH); 
    while(1) {}; //stops throttle from resetting
  }
}

void updateThrottle()
{
  if ((hstate==false)&&(stopped==false)&&RPM<=RPMLimit)
   {
     if ((RPM+sensitivity)<target_speed)
      {
        if(angle > maxAngle){
          angle = maxAngle;
        }
        else{
          //we're going too slow
          angle+=inc_rate;
        }
      }
     if ((RPM-sensitivity)>target_speed)
      {
        //we're going too fast
        if(angle < minAngle){
          angle = minAngle;
        }
        else{
          angle-=dec_rate; 
        }
      }
     throttle.write(angle);  
   }
}
void updateRotations()
{
  ++count; //count revolution for distance
}

void calculateRPM(){
  float timeHalf = endTime - startTime;
  float fullRotateTime = timeHalf / 500; // 2 / 1000, 2 because 2 hall effect sensors, 1000 milliseconds to a second
  RPM = 60 / fullRotateTime;
}

void loop()
{
  checkEndAndRecord();
  //RPM and Revolution Monitoring
  if(digitalRead(hall)==HIGH) //magnet hasnt passed
  {
    hstate = false; //prevent multiple revolution counts in next block
    startTime = millis();
    while (digitalRead(hall)==HIGH)
    {
      checkEndAndRecord();
    }
    endTime = millis();    
  }
  //magnet crosses hall effect
  if (hstate==false)
   {
     //if we start to move, change throttle to throttle meant for movement
     if (haveMoved == false){
       haveMoved = true;
       int clockread1 = analogRead(clockpin); //read once
       delay (15);
       int clockread2 = analogRead(clockpin); //read twice
       clockCutoff=(clockread1+clockread2)/2-clockSensitivity; //average readings and use as set value
       throttle.write(throttle_movement_init);
     }
      updateRotations();
      calculateRPM();
   }
  updateThrottle();
  if(haveMoved){
    SDWriteLn(); //record angle and RPM
  }
  hstate=true;   
 }
  
