#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(String name, byte pin, int mode) : Sensor(name, pin) {
  this->name = name;
  this->SDOpen = false;
  this->_pin = pin;
  this->_mode = MODE_C;
  pinMode(_pin, INPUT);
}

float TemperatureSensor::readValue() {
	int raw_sensor_value = analogRead(_pin);
	//Scaling to 3.3 Volts
	float voltage = (raw_sensor_value * 5.0) / 1024.0;
	//10 mV / degree with 500 mV offset
	float temperatureC = (voltage - 0.5) * 100;
	if(_mode == MODE_C)
	{
		return temperatureC;
	}
	else
	{
		return (temperatureC * 9.0 / 5.0) + 32.0;
	}
}

void TemperatureSensor::setMode(int mode)
{
	_mode = mode;
}

