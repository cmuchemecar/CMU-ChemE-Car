#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include <Arduino.h>
#include "Sensor.h"

#define MODE_C 0
#define MODE_F 1

class TemperatureSensor : public Sensor {

  public:
    TemperatureSensor(String name, byte pin, Timer timer, int mode = MODE_C);
    float readValue();
    void setMode(int mode);
	
  private:
	int _mode;
};

#endif
