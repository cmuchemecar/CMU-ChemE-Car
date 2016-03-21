const int stoppingPin = 9;
const int relayPin =  8;
const int avgTime = 60;
const int voltPin = A0;


void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);      
  pinMode(stoppingPin, INPUT);
  digitalWrite(relayPin, HIGH);  
  Serial.println("Start");
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
  Serial.println(VoltMeasurement() + " V");
  
  if (avgSwitchValue >= 0.7) {     
    digitalWrite(relayPin, LOW);  
    Serial.println("Stop");
    while(1) {}
  } 
}

String VoltMeasurementRaw(){
  float volt = analogRead(voltPin);
  return floatPrint(volt);
}

String VoltMeasurement(){
 //return a string representing the voltage
  float volt = analogRead(voltPin);
  volt = volt / 1024 * 5; //Arduino scaling
  volt = volt * 430 / 100; //Voltage divider
  return floatPrint(volt);
}

String floatPrint(float x){
  int intp = x;
  int fracp = (x - intp) * 1000;
  if(fracp < 0){
    fracp = -1 * fracp;
  }
  return (String(intp) + "." + String(fracp));
}
