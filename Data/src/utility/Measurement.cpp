#include "Measurement.h"

Measurement::Measurement(String name, float (*measureValue)(), Timer timer) {
  this->_name = name;
  this->_measureValue = measureValue;
  this->_timer = timer;
  this->_SDOpen = false;
}

void Measurement::update() {
    _value = _measureValue();
    _time = _timer.duration();
}

void Measurement::print(int dec) {
  Serial.print(FloatToString(_value, dec));
}

void Measurement::println(int dec) {
  Serial.println(FloatToString(_value, dec));
}


