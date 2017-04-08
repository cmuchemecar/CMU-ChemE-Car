#include "MotorActuator.h"

MotorActuator::MotorActuator(String name, byte pin, Timer timer) 
    : Actuator(name, pin, timer) {
    this->_name = name;
    this->_pin = pin;
    this->_timer = timer;
    this->_SDOpen = false;
    pinMode(_pin, OUTPUT);
}

void MotorActuator::start() {
    digitalWrite(_pin, HIGH);
    _value = 1.0;
    _time = _timer.duration();
}

void MotorActuator::stop() {
    digitalWrite(_pin, LOW);
    _value = 0.0;
    _time = _timer.duration();
}