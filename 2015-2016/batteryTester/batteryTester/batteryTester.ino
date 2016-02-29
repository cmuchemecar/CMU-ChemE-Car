const int stoppingPin = 9;
const int relayPin =  8;
const int avgTime = 60;


void setup() {
  pinMode(relayPin, OUTPUT);      
  pinMode(stoppingPin, INPUT);
  digitalWrite(relayPin, HIGH);  
}

void loop(){
  
  int counter = 0;
  int sumSwitchValue = 0;
  while(counter < avgTime) {
    sumSwitchValue += digitalRead(stoppingPin);
    counter ++;
    delay(1);
  }
  float avgSwitchValue = ((float)(sumSwitchValue))/
  ((float)(counter));
  
  if (avgSwitchValue >= 0.7) {     
    digitalWrite(relayPin, LOW);  
    while(1) {}
  } 
}
