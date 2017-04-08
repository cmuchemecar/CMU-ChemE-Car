#ifndef MOTORACTUATOR_H
#define MOTORACTUATOR_H

#include <Arduino.h>
#include "Actuator.h"

class MotorActuator : public Actuator {

  friend class DataClass;

  public:
    MotorActuator(String name, byte pin, Timer timer);
	void start();
	void stop();

};

#endif
