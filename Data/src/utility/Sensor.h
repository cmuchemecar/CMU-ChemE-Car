#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include "Utility.h"
#include "Timer.h"

class Sensor {

  public:
    Sensor(String name, byte pin);
    virtual float readValue();
	int readAnalog();
	int readDigital();
    void print(int dec = DEFAULTDEC);
	void println(int dec = DEFAULTDEC);
	
	String name;
	bool SDOpen;

  private:
	byte _pin;
};

#endif
