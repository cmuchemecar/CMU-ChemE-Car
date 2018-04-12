#include "INA219CurrentSensor.h"

INA219CurrentSensor::INA219CurrentSensor(String name, Timer timer)
    : Sensor(name, 200, timer) {
    this->_name = name;
    this->_timer = timer;
    this->_SDOpen = false;
}

float INA219CurrentSensor::readValue() {
	Adafruit_INA219 _ina219;
	_ina219.begin();
	return _ina219.getCurrent_mA();
}

void INA219CurrentSensor::resetTimer() {
    this->_timer.reset();
}
