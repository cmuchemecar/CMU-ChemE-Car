#include "PhotoSensor.h"

PhotoSensor::PhotoSensor(String name, byte pin, float R)
    : Sensor(name, pin) {
    this->name = name;
    this->SDOpen = false;
    this->_pin = pin;
    this->_R = R;
    pinMode(_pin, INPUT);
}

float PhotoSensor::readValue() {
    float resistance = ((MAXANALOG / analogRead(_pin)) * _R) - _R;

    if (resistance < 0) {
    	return 0;
    }
    else {
    	return resistance;
    }
}
