#include "VoltageSensor.h"

VoltageSensor::VoltageSensor(String name, byte pin, float R1,
  float R2) : Sensor(name, pin) {
  this->name = name;
  this->SDOpen = false;
  this->_pin = pin;
  this->_R1 = R1;
  this->_R2 = R2;
  pinMode(_pin, INPUT);
}

float VoltageSensor::readValue() {
  float voltage = Scale(analogRead(_pin)) * ((_R1+_R2)/_R2);
  
  if (voltage < 0) {
  	return 0;
  }
  else {
  	return voltage;
  }
}

