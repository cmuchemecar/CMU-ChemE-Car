#include <SD.h>
#define hallpin 2
#define voltpin1 0
#define ammpin1 1
long epoch;
long last_write_time;
int hall_measurement;
boolean change;

// Setting up SD Card 
char filename[] = "DATAFILE.txt"; //name of the file to save data to
File data;

void setup(){
  epoch = millis();
  last_write_time = epoch;
  Serial.begin(9600); //transmission is 9600 bits per second 
  
  //setting up SD
  pinMode(10, OUTPUT);
  SD.begin(10);
  
  //set baseline for the hall sensor  
  hall_measurement = digitalRead(hallpin);
  change = false;
  
  //have a clear line separator for new runs  
  data = SD.open(filename, FILE_WRITE);
  data.println("-----------------------------------------------------------");
  data.close();
}

String HallMeasurement(){
  //if the sensor detects a pass of a magnet on the tire
  //then set the new value and indicate there has been a change
  if( digitalRead(hallpin) != hall_measurement){
    change = true;
    hall_measurement = !(hall_measurement);
  }
  else{
    change = false;
  }  
  return String(hall_measurement);  // Range : 0 or 1
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

String AmmMeasurement(){
  float amp1 = analogRead(ammpin1);
  float amp = amp1;
  Serial.println("raw milliamps: " + floatPrint(amp));
  //1.5 milliamps => .3 mV = 5 ratio
  // take input reading
  // then multiply by 4.9 mV
  // times by 5 to get how many milli amps it is
  amp = amp * 4.9;
  amp = amp * 5;
  Serial.println("milliamps: " + floatPrint(amp));
  return floatPrint(amp);
}

void SDWriteLn(String hall, String volt, String amp) {
  data = SD.open(filename, FILE_WRITE);
  data.println(hall + ", " + volt + ", " + amp + ", " + String(millis() - epoch));
  data.close();
}

void loop(){
  HallMeasurement();
  //every quarter second, record the state of the car
  if (millis() >= last_write_time + 250){
    SDWriteLn(HallMeasurement(), VoltMeasurement(), AmmMeasurement());
    last_write_time = millis();
  }
  //if the tire magnet has passes the sensor, then write
  else if (change){
    SDWriteLn(String(hall_measurement), VoltMeasurement(), AmmMeasurement());
    last_write_time = millis();
  }
}
