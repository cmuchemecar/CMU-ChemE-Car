#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include <Arduino.h>
#include "Sensor.h"

class TemperatureSensor : public Sensor {

  public:
    TemperatureSensor(String name, int pin, float R1, float R2);
    float readValue();
	
  private:
	int _pin;
	float _R1;
	float _R2;
};

#endif
