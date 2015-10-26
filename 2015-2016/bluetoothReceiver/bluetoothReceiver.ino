#include <SPI.h>
#include <Adafruit_MAX31855.h>

#define DO 2
#define CS 3
#define CLK 4

Adafruit_MAX31855 thermocouple(CLK, CS, DO);
long start_time;

void setup() {
  Serial.begin(9600);  
  start_time = millis();
  delay(500);
}

void loop() {
  float temperature = thermocouple.readCelsius();
  Serial.println(floatPrint(temperature) + ", "+ String(millis() - start_time));
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
