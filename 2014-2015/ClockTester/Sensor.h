#ifndef Sensor_h
#define Sensor_h

#include "Arduino.h"
/*
Sensor.h is the header file for the generic class for reading
from a pin. It makes no assumption regarding analog vs digital, 
but still has the virtual headers for subclass implementation.
*/
class Sensor
{
	public:
		Sensor(int pin);
		Sensor(int pin, float scalingFactor);
		virtual int readRaw();
		virtual int readScaled();
		virtual String getStringRaw();
		virtual String getStringScaled();
		virtual void printRaw();
		virtual void printScaled();
	private:
		int _pin;
		float _scalingFactor;
};
#endif
