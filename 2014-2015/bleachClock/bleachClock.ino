int photoresistor = 3; //which analog pin the photoresitor reading is coming from
int reading; //the value read from the photoresistor
unsigned long time; //how long since the arduino turned on
unsigned long startTime; // the starting time of the reaction
unsigned long endTime; //the ending time of the reaction
unsigned long runTime; //total length of time the reaction took
boolean started; //bool for if the reaction started yet or not
boolean endOccured; //bool for if the reaction ended yet or not
String toStart = String("Reaction yet to start with reading ");
String reacting = String("Reaction underway with reading ");
String ended = String("Reaction ended with reading ");
String timer = String("Current time since arduino turned on is ");
String endTimeString = String("Reaction took this many seconds long ");

//You can change the two values below based on what values you get when actually testing 
int reactionStart = 800; //the value the photoresistor reads before the reaction starts
int reactionEnd = 200; //the value the photoresistor reads when the reaction ends

int delayTime = 1000; //how long you want to delay between readings, in milliSeconds


void setup(){
  Serial.begin(9600);
  time = millis(); //start the timer
  started = false;
  endOccured = false;
}

void loop()
{
  reading = analogRead(photoresistor);
  if(reading > reactionStart){
    Serial.println(toStart + reading);
  }
  else if (reactionEnd < reading && reading < reactionStart){
    if(!started){
      started = true;
      startTime = millis();
    }
    Serial.println(reacting + reading);
  }
  else if (reading <= reactionEnd && (!endOccured)){
    endOccured = true;
    endTime = millis();
    runTime = (endTime - startTime) / 1000;
    Serial.println(endTimeString + runTime);
    Serial.println(ended + reading);
  }
  Serial.println(timer + (millis() - time)/1000);

  delay(delayTime);   
}


