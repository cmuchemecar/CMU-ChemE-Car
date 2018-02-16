#ifndef INA219CURRENTSENSOR_H
#define INA219CURRENTSENSOR_H

#include <Arduino.h>
#include "Sensor.h"
#include <Adafruit_INA219.h>


class INA219CurrentSensor : public Sensor {
	
    public:
        INA219CurrentSensor(String name, Timer timer);
        float readValue();
};

#endif
