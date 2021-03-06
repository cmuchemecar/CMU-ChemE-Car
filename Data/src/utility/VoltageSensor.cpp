#include "VoltageSensor.h"

VoltageSensor::VoltageSensor(String name, byte pin, Timer timer, float R1,
  float R2) : Sensor(name, pin, timer) {
  this->_name = name;
  this->_pin = pin;
  this->_timer = timer;
  this->_SDOpen = false;
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

