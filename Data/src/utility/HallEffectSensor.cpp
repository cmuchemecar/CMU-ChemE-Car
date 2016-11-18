#include "HallEffectSensor.h"

HallEffectSensor::HallEffectSensor(String name, byte pin): Sensor(name, pin) {
    this->name = name;
    this->SDOpen = false;
    this->_pin = pin;
    pinMode(_pin, INPUT);
}

bool HallEffectSensor::magnetNear() {
    return digitalRead(_pin);
}

float HallEffectSensor::readValue() {
  return 1.0;
}
