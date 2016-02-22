const int stoppingPin = 9;
const int relayPin =  8;



void setup() {
  pinMode(relayPin, OUTPUT);      
  pinMode(stoppingPin, INPUT);
  digitalWrite(relayPin, HIGH);  
}

void loop(){
  int switchValue = digitalRead(stoppingPin);

  if (buttonState == HIGH) {     
    digitalWrite(relayPin, LOW);  
    while(1) {}
  } 
  
