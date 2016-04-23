#include "Sensor.h"

Sensor::Sensor(String name, int pin) {
  this->name = name;
  this->_pin = pin;
  pinMode(_pin, INPUT);
}

float Sensor::readValue() {
  return analogRead(_pin);
}

int Sensor::readAnalog() {
  return analogRead(_pin);
}

int Sensor::readDigital() {
  return digitalRead(_pin);
}

void Sensor::print(int dec) {
  Serial.print(FloatToString(readValue(), dec));
}

void Sensor::println(int dec) {
  Serial.println(FloatToString(readValue(), dec));
}


