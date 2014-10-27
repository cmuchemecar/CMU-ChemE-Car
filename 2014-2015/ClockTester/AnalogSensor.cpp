#include <String>
#include "Arduino.h"
#include "AnalogSensor.h"

AnalogSensor::AnalogSensor(int pin)
{
	pinMode(pin, INPUT);
	_pin = pin;
	_scalingFactor = 1.0;
}

AnalogSensor::AnalogSensor(int pin, float scalingFactor)
{
	pinMode(pin, INPUT);
	_pin = pin;
	_scalingFactor = scalingFactor;
}

String floatPrint(float x){
  int intp = x;
  int fracp = (x - intp) * 1000;
  if(fracp < 0){
    fracp = -1 * fracp;
  }
  return (String(intp) + "." + String(fracp));
}

int AnalogSensor::readRaw()
{
	int val = analogRead(_pin);
	return val;
}

float AnalogSensor::readScaled()
{
	int val = analogRead(_pin);
	float raw_ans = ((float)val) * _scalingFactor;
	return raw_ans;
}

String AnalogSensor::getStringRaw()
{
	int raw = readRaw();
	return String(raw);
}

String AnalogSensor::getStringScaled()
{
	float raw = readScaled();
	return floatPrint(raw);
}

void AnalogSensor::printRaw()
{
	Serial.println(getStringRaw());
}

void AnalogSensor::printScaled()
{
        Serial.println(getStringScaled());
}

