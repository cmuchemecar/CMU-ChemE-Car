#ifndef PHOTOSENSOR_H
#define PHOTOSENSOR_H

#include <Arduino.h>
#include "Sensor.h"

class PhotoSensor : public Sensor {
	
    public:
        PhotoSensor(String name, byte pin, Timer timer, float R);
        float readValue();

    private:
        float _R;
};

#endif
