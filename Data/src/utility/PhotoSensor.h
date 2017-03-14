#ifndef PHOTOSENSOR_H
#define PHOTOSENSOR_H

#include <Arduino.h>
#include "Sensor.h"

class PhotoSensor : public Sensor {
	
    public:
        PhotoSensor(String name, byte pin, float R);
        float readValue();

    private:
        byte _pin;
        float _R;
};

#endif
