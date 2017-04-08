#include "Measurement.h"

Measurement::Measurement(String name, float (*measureValue)(), Timer timer) {
  this->_name = name;
  this->_measureValue = measureValue;
  this->_timer = timer;
  this->_SDOpen = false;
  this->_value = 0.0;
  this->_updated = false;
}

float Measurement::getValue() {
  return _value;
}

void Measurement::update() {
    if (!_updated) {
      _updated = true;
    }

    _value = _measureValue();
    _time = _timer.duration();
}

bool Measurement::updated() {
  return _updated;
}

void Measurement::reset() {
  _SDOpen = false;
  _value = 0.0;
  _updated = false;
}

void Measurement::print(int dec) {
  Serial.print(FloatToString(_value, dec));
}

void Measurement::println(int dec) {
  Serial.println(FloatToString(_value, dec));
}


