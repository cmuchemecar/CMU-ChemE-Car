#ifndef VOLTAGESENSOR_H
#define VOLTAGESENSOR_H

#include <Arduino.h>
#include "Sensor.h"

class VoltageSensor : public Sensor {

  public:
    VoltageSensor(String name, byte pin, Timer timer, float R1, float R2);
    float readValue();
	
  private:
	float _R1;
	float _R2;
};

#endif
