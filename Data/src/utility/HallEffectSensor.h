#ifndef HALLEFFECTSENSOR_H
#define HALLEFFECTSENSOR_H

#include <Arduino.h>
#include "Sensor.h"

class HallEffectSensor : public Sensor {
    public:
        HallEffectSensor(String name, byte pin);
        bool magnetNear();
        float readValue();

    private:
        byte _pin;
};

#endif
