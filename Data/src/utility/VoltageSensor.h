#ifndef VOLTAGESENSOR_H
#define VOLTAGESENSOR_H

#include <Arduino.h>
#include "Sensor.h"

class VoltageSensor : public Sensor {

  public:
    VoltageSensor(String name, int pin, int R1, int R2);
    float readValue();
	
  private:
	int _pin;
	int _R1;
	int _R2;
};

#endif
