#ifndef PHOTOSENSOR_H
#define PHOTOSENSOR_H

#include <Arduino.h>
#include "Sensor.h"

class PhotoSensor : public Sensor {
    public:
        PhotoSensor(String name, int pin, float R);
        float readValue();

    private:
        int _pin;
        float _R;
};

#endif
