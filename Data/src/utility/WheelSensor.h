#ifndef WHEELSENSOR_H
#define WHEELSENSOR_H

#include <Arduino.h>
#include "Sensor.h"
#include "HallEffectSensor.h"

class WheelSensor : public Sensor {

    public:
        WheelSensor(String name, byte pin, float wheelRadius, int numMagnets);
        float readValue();
        bool passed();
        int ticks();
        int revolutions();
        void reset();

        volatile bool _passed;
        volatile int _ticks;

    private:
        byte _pin;
        float _wheelRadius;
        int _numMagnets;
};

#endif
