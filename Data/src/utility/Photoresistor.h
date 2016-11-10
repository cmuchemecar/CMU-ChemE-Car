#ifndef PHOTORESISTOR_H
#define PHOTORESISTOR_H

#include <Arduino.h>
#include "Sensor.h"

class Photoresistor : public Sensor {
    public:
        Photoresistor(String name, byte pin, float R1);
        float readValue();

    private:
        int _pin;
        float _R1;
};

#endif
