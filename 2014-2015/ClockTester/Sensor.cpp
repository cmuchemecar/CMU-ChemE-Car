#include <String>
#include "Arduino.h"
#include "Sensor.h"

Sensor::Sensor(int pin)
{
	pinMode(pin, INPUT);
	_pin = pin;
	_scalingFactor = 1;
}

Sensor::Sensor(int pin, float scalingFactor)
{
	pinMode(pin, INPUT);
	_pin = pin;
	_scalingFactor = scalingFactor;
}

int Sensor::readRaw()
{
	int val = analogRead(_pin);
	return val;
}

int Sensor::readScaled()
{
	int val = analogRead(_pin);
	float raw_ans = ((float)val) * _scalingFactor;
	return (int)raw_ans;
}

String Sensor::getStringRaw()
{
	int raw = readRaw();
	return String(raw);
}

String Sensor::getStringScaled()
{
	int raw = readScaled();
	return String(raw);
}

void Sensor::printRaw()
{
	Serial.println(getStringRaw());
}

void Sensor::printScaled()
{
        Serial.println(getStringScaled());
}

