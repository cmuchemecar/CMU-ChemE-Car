#include "PhotoSensor.h"

PhotoSensor::PhotoSensor(String name, byte pin, Timer timer, float R)
    : Sensor(name, pin, timer) {
    this->_name = name;
    this->_pin = pin;
    this->_timer = timer;
    this->_SDOpen = false;
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
