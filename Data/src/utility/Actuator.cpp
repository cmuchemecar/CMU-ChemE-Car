#include "Actuator.h"

Actuator::Actuator(String name, byte pin, Timer timer) {
  this->_name = name;
  this->_pin = pin;
  this->_timer = timer;
  this->_SDOpen = false;
  pinMode(_pin, OUTPUT);
}

void Actuator::writeAnalog(int value) {
  analogWrite(_pin, value);
  _value = (float) value;
  _time = _timer.duration();
}

void Actuator::writeDigital(int value) {
  digitalWrite(_pin, value);
  _value = (float) value;
  _time = _timer.duration();
}

void Actuator::print() {
  Serial.print(_value);
}

void Actuator::println() {
  Serial.println(_value);
}