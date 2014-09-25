#define voltpin1 0
long epoch;

void setup(){
  epoch = millis();
  Serial.begin(9600); //transmission is 9600 bits per second
  Serial.println("#S|BATTERY|[-------------------------------------------------------------------]#");
}


String VoltMeasurement(){
  //return a string representing the voltage
  float volt = analogRead(voltpin1);
  volt = volt * (0.00488);
  volt = volt / 5;
  volt = volt * 20;
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

void loop(){
  epoch = millis();
  
  //save the volt measurement to file
  Serial.print("#S|BATTERY|[");
  Serial.print(VoltMeasurement());
  Serial.println("]#");
  
  if (epoch < 300000) delay(10000); //delay 10s for first 5min
  else if (epoch < 3900000) delay(60000); // delay 1min for next 1hr
  else delay(86400000); //delay 1day
}
