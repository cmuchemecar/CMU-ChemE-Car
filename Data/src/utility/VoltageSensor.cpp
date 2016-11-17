#include "VoltageSensor.h"

VoltageSensor::VoltageSensor(String name, int pin, int R1,
  int R2) : Sensor(name, pin) {
  this->name = name;
  this->SDOpen = false;
  this->_pin = pin;
  this->_R1 = R1;
  this->_R2 = R2;
  pinMode(_pin, INPUT);
}

float VoltageSensor::readValue() {
  return Scale(analogRead(_pin)) * (_R2/(_R1+_R2));
}

