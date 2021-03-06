#define inputpin 0
#define thresh 300

unsigned long startTime;
unsigned long endTime;

//This will stop the car if the average of the currently read value
//and the previously read value is past the threshold point

//Previous value read by the photoresistor
int prevValue;
//Average of the previous value and the current value
//read by the photoresistor
int avg;


void setup()
{
  Serial.begin(9600);
  Serial.println("-------------------");
  Serial.println("Begin run");
  
  //Get current system time
  startTime = millis();

}

void loop()
{
  
  int input = analogRead(inputpin);
  
  avg = (input + prevValue)/2;
  
  if(avg > thresh)
  {
    Serial.print("Input value is:");
    Serial.println(input);
  }
  else
  {
    endTime = millis();
    Serial.print("Final input value is:");
    Serial.println(input);
    Serial.println("\n\n\n\n\n");
    Serial.println("Car is stopped");
    unsigned long runMillis = endTime-startTime;
    Serial.print("Run time (in milliseconds: ");
    Serial.println(runMillis);
    Serial.println("-------------------");
    while(1);
  }
  
  prevValue = input;
  
}
