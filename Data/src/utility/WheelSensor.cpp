#include "WheelSensor.h"

WheelSensor* _wheelSensor;
void _handleInterrupt();

WheelSensor::WheelSensor(String name, byte pin, Timer timer,
    float wheelRadius, int numMagnets) : Sensor(name, pin, timer) {
    this->_name = name;
    this->_pin = pin;
    this->_timer = timer;
    this->_SDOpen = false;
    this->_wheelRadius = wheelRadius;
    this-> _numMagnets = numMagnets;
    this->_passed = false;
    this-> _ticks = 0;
    pinMode(_pin, INPUT_PULLUP);

    _wheelSensor = this;

    attachInterrupt(digitalPinToInterrupt(_pin), _handleInterrupt, FALLING);
}

float WheelSensor::readValue() {
    return ((PI * _wheelRadius * 2) / _numMagnets) * _ticks;
}

bool WheelSensor::passed() {
    return _passed;
}

int WheelSensor::ticks() {
    return _ticks;
}

int WheelSensor::revolutions() {
    return _ticks / _numMagnets;
}

void WheelSensor::reset() {
    _passed = false;
    _ticks = 0;
}

void _handleInterrupt() {
    _wheelSensor->_passed = true;
    _wheelSensor->_ticks++;
}