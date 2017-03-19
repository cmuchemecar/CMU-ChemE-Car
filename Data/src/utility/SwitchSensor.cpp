#include "SwitchSensor.h"

SwitchSensor::SwitchSensor(String name, byte pin): Sensor(name, pin) {
    this->name = name;
    this->SDOpen = false;
    this->_pin = pin;
    pinMode(_pin, INPUT);
}

float SwitchSensor::readValue() {
  int switchValue = digitalRead(_pin);

  if (switchValue) {
    return 1.0;
  }
  else {
    return 0.0;
  }
}

bool SwitchSensor::on() {
  int switchValue = digitalRead(_pin);

  if (switchValue) {
    return true;
  }
  else {
    return false;
  }
}

void SwitchSensor::waitForOn() {
    while(1) {
      if (SwitchSensor::on()) {
        break;
      }
    }
}

void SwitchSensor::waitForOff() {
    while(1) {
      if (!SwitchSensor::on()) {
        break;
      }
    }
}
