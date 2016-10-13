#include "Photoresistor.h"

Photoresistor::Photoresistor(String name, byte pin, float R1)
    : Sensor(name, pin) {
    this->name = name;
    this->SDOpen = false;
    this->_pin = pin;
    this->_R1 = R1;
    pinMode(_pin, INPUT);
}

float Photoresistor::readValue() {
    return Scale(analogRead(_pin) * _R1);
}
