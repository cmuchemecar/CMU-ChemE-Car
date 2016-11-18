#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(String name, int pin, float R1,
  float R2) : Sensor(name, pin) {
  this->name = name;
  this->SDOpen = false;
  this->_pin = pin;
  this->_R1 = R1;
  this->_R2 = R2;
  pinMode(_pin, INPUT);
}

float TemperatureSensor::readValue() {
  return (Scale(analogRead(_pin)) * (_R2/(_R1+_R2)))*100 - 37;
}
