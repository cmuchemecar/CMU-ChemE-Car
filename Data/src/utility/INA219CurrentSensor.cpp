#include "INA219CurrentSensor.h"

INA219CurrentSensor::INA219CurrentSensor(String name, Timer timer)
    : Sensor(name, -1, timer) {
    this->_name = name;
    this->_timer = timer;
    this->_SDOpen = false;
    _ina219.begin();
}

float INA219CurrentSensor::readValue() {
    Serial.println("before");
    float x = _ina219.getCurrent_mA() / 1000.0;
    Serial.println("after");
    return x;
}
