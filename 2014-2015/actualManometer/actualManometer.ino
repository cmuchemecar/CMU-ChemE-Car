int inputPin = A0;
int threshold = 500;
int relayOut = 2;

int startTime;
int endTime;
int runMillis;
int runSecs;

int hall_S = 1;
boolean hstate_S = true;
boolean stopped_S = false;
long count_S = 0; // total number of rotations before car stops
float RPM_S = 0;
double circum_S = 39.9;
int angle_S;
long starting_S;
long startTime_S;
long endTime_S;
long howLongToRun_S = 10000;

void setup()
{
  pinMode(relayOut, OUTPUT);
  Serial.begin(9600);
  Serial.println("-------------------");
  Serial.println("Begin run");
  digitalWrite(relayOut, HIGH);
  startTime = millis();
  
  pinMode(hall_S, INPUT);
  starting_S = millis();
}





String floatPrint(float x){
  int intp = x;
  int fracp = (x - intp) * 1000;
  if(fracp < 0){
    fracp = -1 * fracp;
  }
  return (String(intp) + "." + String(fracp));
}

void checkEndAndRecord(){
  if ((millis() - starting_S) >= howLongToRun_S) //end switch flipped or iodine end
  {
    stopped_S = true;
    long distance = count_S*circum_S / 2;
  }
}


void updateRotations()
{
  ++count_S; //count revolution for distance
  Serial.print("Count = ");
  Serial.println(count_S);
}

void calculateRPM(){
  float timeHalf = endTime_S - startTime_S;
  float fullRotateTime = timeHalf / 500; // 2 / 1000, 2 because 2 hall effect sensors, 1000 milliseconds to a second
  RPM_S = 60 / fullRotateTime;
  Serial.print("RPM = ");
  Serial.println(RPM_S);
}




void loop()
{
  
  
  int manoValue = analogRead(inputPin);
  Serial.print("Input value: ");
  Serial.println(manoValue);
  
  //BEGIN SPEED CODE
  
  checkEndAndRecord();
  //RPM and Revolution Monitoring
  if(analogRead(hall_S) < 50) //magnet hasnt passed
  {
    hstate_S = false; //prevent multiple revolution counts in next block
    startTime_S = millis();
    while (analogRead(hall_S) < 50)
    {
      checkEndAndRecord();
    }
      endTime_S = millis();
  }
  //magnet crosses hall effect
  if (hstate_S==false)
  {
    updateRotations();
    calculateRPM();
  }
  hstate_S=true; 
  
  //END SPEED CODE
  
  if (manoValue < threshold)
  {
    endTime = millis();
    Serial.println("\n\n\n\n\n");
    Serial.println("Car is stopped");
    runMillis = endTime-startTime;
    float runSecs = runMillis/1000;
    Serial.print("Run time (seconds): ");
    Serial.println(runSecs);
    Serial.println("-------------------");
    digitalWrite(relayOut, LOW);
    while(1);
  }
  else
  {
    Serial.print("Input value: ");
    Serial.println(manoValue);
  }
  
  
}
