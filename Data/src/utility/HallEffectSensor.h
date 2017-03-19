#ifndef HALLEFFECTSENSOR_H
#define HALLEFFECTSENSOR_H

#include <Arduino.h>
#include "Sensor.h"

class HallEffectSensor : public Sensor {

    public:
        HallEffectSensor(String name, byte pin);
        float readValue();
        bool touched();
        bool on();
        void reset();

    private:
    	byte _pin;
        bool _touched;
};

#endif
