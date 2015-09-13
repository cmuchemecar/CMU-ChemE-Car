int inputPin = A0;
int threshold = 0;
int relayOut = 2;

unsigned long startTime;
unsigned long endTime;
unsigned long runMillis;
unsigned long runSecs;

void setup()
{
  pinMode(relayOut, OUTPUT);
  Serial.begin(9600);
  Serial.println("-------------------");
  Serial.println("Begin run");
  digitalWrite(relayOut, HIGH);
  startTime = millis();
}

void loop()
{
  
  
  int manoValue = analogRead(inputPin);
  Serial.print("Input value: ");
  Serial.println(manoValue);
  
  if (manoValue <= threshold)
  {
    endTime = millis();
    Serial.println("\n\n\n\n\n");
    Serial.println("Car is stopped");
    runMillis = endTime-startTime;
    Serial.print("Run time (millis): ");
    Serial.println(runMillis);
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
