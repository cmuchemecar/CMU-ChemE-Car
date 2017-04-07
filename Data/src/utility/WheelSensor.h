#ifndef WHEELSENSOR_H
#define WHEELSENSOR_H

#include <Arduino.h>
#include "Sensor.h"
#include "HallEffectSensor.h"

class WheelSensor : public Sensor {

    public:
        WheelSensor(String name, byte pin, Timer timer,
            float wheelRadius, int numMagnets);
        float readValue();
        bool passed();
        int ticks();
        int revolutions();
        void reset();

        volatile bool _passed;
        volatile int _ticks;

    private:
        float _wheelRadius;
        int _numMagnets;
};

#endif
