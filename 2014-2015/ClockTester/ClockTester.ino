#include "AnalogSensor.h"

#define photopin 3 //input pin
#define delaytime 100 //interval for reading photoresistor (ms)
long epoch;

AnalogSensor photoresistor(photopin);

void setup()
{
  epoch = millis();
  Serial.begin(9600);
  Serial.println("#S|CLOCK|[-------------------------------------------------------------------]#");
}
 
void loop()
{
  Serial.print("#S|CLOCK|[");
  //Serial.print((String(millis() - epoch)));
  //Serial.print(", ");
  Serial.print(photoresistor.getStringRaw());
  Serial.println("]#");
  delay(delaytime);
}  
