#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>
#include "Utility.h"
#include "Timer.h"

class Actuator {

  friend class DataClass;

  friend class MotorActuator;

  public:
    Actuator(String name, byte pin, Timer timer);
    float getValue();
	void writeAnalog(int value);
	void writeDigital(int value);
	void reset();
	void print();
	void println();

  private:
  	String _name;
	byte _pin;
	Timer _timer;
	bool _SDOpen;
	float _time;
	float _value;
};

#endif
