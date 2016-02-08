#include <SPI.h>
#include <Adafruit_MAX31855.h>


#define DO 2
#define CS 3
#define CLK 4

Adafruit_MAX31855 thermocouple(CLK, CS, DO);
long start_time;
String value;
int start, stop_flag;

void setup() {
  Serial.begin(9600);
  start_time = millis();
  start = 0;
  stop_flag = 0;
  delay(500);
}

void loop() {
  float temperature = thermocouple.readCelsius();
  value = floatPrint(temperature) + ", "+ String(millis() - start_time);
  if (start_time > 1000 && start == 0) {
    Serial.println("Start");
    start = 1;
  }
  if (start_time >10000 && stop_flag == 0){
    Serial.println("Stop");
    stop_flag = 1;
  }
  Serial.println(value);
  delay(1000);
}


String floatPrint(float x){
  int intp = x;
  int fracp = (x - intp) * 1000;
  if(fracp < 0){
    fracp = -1 * fracp;
  }
  return (String(intp) + "." + String(fracp));
}


