#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include <Arduino.h>
#include "Sensor.h"
#define MODE_C 0
#define MODE_F 1

class TemperatureSensor : public Sensor {

  public:
    TemperatureSensor(String name, int pin, int mode = MODE_C);
    float readValue();
    int setMode(int mode);
	
  private:
	int _pin;
	int _mode;
};

#endif
