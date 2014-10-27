#ifndef AnalogSensor_h
#define AnalogSensor_h

#include "Arduino.h"
/*
Sensor.h is the header file for the generic class for reading
from a pin. It makes no assumption regarding analog vs digital, 
but still has the virtual headers for subclass implementation.
*/
class AnalogSensor
{
	public:
		AnalogSensor(int pin);
		AnalogSensor(int pin, float scalingFactor);
		int readRaw();
		float readScaled();
		String getStringRaw();
		String getStringScaled();
		void printRaw();
		void printScaled();
	private:
		int _pin;
		float _scalingFactor;
};
#endif
