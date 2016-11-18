#include "PhotoSensor.h"

PhotoSensor::PhotoSensor(String name, int pin, int R)
    : Sensor(name, pin) {
    this->name = name;
    this->SDOpen = false;
    this->_pin = pin;
    this->_R = R;
    pinMode(_pin, INPUT);
}

float PhotoSensor::readValue() {
    return ((MAXANALOG / analogRead(_pin)) - 1) * _R;
}
