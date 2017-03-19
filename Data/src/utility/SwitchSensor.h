#ifndef SWITCHSENSOR_H
#define SWITCHSENSOR_H

#include <Arduino.h>
#include "Sensor.h"

class SwitchSensor : public Sensor {

    public:
        SwitchSensor(String name, byte pin);
        float readValue();
        bool on();
        void waitForOn();
        void waitForOff();

    private:
    	byte _pin;
};

#endif
