#include "HallEffectSensor.h"

HallEffectSensor::HallEffectSensor(String name, byte pin, Timer timer)
    : Sensor(name, pin, timer) {
    this->_name = name;
    this->_pin = pin;
    this->_timer = timer;
    this->_SDOpen = false;
    this->_touched = false;
    pinMode(_pin, INPUT);
}

float HallEffectSensor::readValue() {
  int halleffect = digitalRead(_pin);

  if (!halleffect) {
    _touched = true;
    return 1.0;
  }
  else {
    return 0.0;
  }
}

bool HallEffectSensor::touched() {
    return _touched;
}

bool HallEffectSensor::on() {
  int halleffect = digitalRead(_pin);

  if (!halleffect) {
    _touched = true;
    return true;
  }
  else {
    return false;
  }
}

void HallEffectSensor::reset() {
    _touched = false;
}
