const int stoppingPin = 9;
const int relayPin =  8;
const int avgTime = 60;
const int voltPin = A0;
const int ammPin = A1;
const int hallPin = A5;

int hallValue = 0;

unsigned long startTime;
unsigned long currentTime;
unsigned long prevPrintTime;
unsigned long printTime;


void setup() {
  Serial.begin(9600);
  pinMode(hallPin, INPUT);
  pinMode(relayPin, OUTPUT);      
  pinMode(stoppingPin, INPUT);
  digitalWrite(relayPin, HIGH);  
  Serial.println("Start");
  startTime = millis();
  prevPrintTime = startTime;
}

void loop(){
  currentTime = millis() - startTime;
  String t = (String) currentTime;
  printTime = millis() - prevPrintTime;
  
  int counter = 0;
  int sumSwitchValue = 0;
  while(counter < avgTime) {
    sumSwitchValue += digitalRead(stoppingPin);
    counter ++;
    delay(1);
  }
  float avgSwitchValue = ((float)(sumSwitchValue))/
  ((float)(counter));
  
  if (printTime > 1000) {
    prevPrintTime = millis();
    float Vout = ReadVout(100, 3);
    float current = ReadCurrent(Vout);
    hallValue = analogRead(hallPin);
  
    sendValue("Volt", t, VoltMeasurement());
    sendValue("Current", t, floatPrint(current*1000));
    sendValue("Hall", t, (String) hallValue);
  }
  
  if (avgSwitchValue >= 0.7) {     
    digitalWrite(relayPin, LOW);  
    Serial.println("Stop");
    while(1) {}
  }
}

void sendValue(String sensorName, String t, String value) {
  Serial.println(sensorName + ", " + t + ", " + value);
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

float ReadVout(float t, float v)
  {
    float total_delay = t;
    float value_delay = v;
    float voltage_sum = 0.0, Vout = 0.0;
    int i = 0, count = 0;
    while(i<=total_delay)
    {
      delay(value_delay);
      voltage_sum += (analogRead(ammPin)*5./1023.);
      count++;
      i += value_delay;
    }
    Vout = voltage_sum/count;
    return Vout;
  }
  
float ReadCurrent(float Vout)
  {
    float Vref = 2.85;
    float current = (Vout - Vref)*(-0.160/125.0);
    return current*1000;
  }
