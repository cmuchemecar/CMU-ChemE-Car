#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include "Utility.h"
#include "Timer.h"

class Sensor {

  friend class DataClass;

  friend class VoltageSensor;
  friend class TemperatureSensor;
  friend class HallEffectSensor;
  friend class WheelSensor;
  friend class PhotoSensor;
  friend class SwitchSensor;

  public:
    Sensor(String name, byte pin, Timer timer);
    virtual float readValue();
	  int readAnalog();
	  int readDigital();
    void reset();
    void print(int dec = DEFAULTDEC);
	  void println(int dec = DEFAULTDEC);

  private:
  	String _name;
	  byte _pin;
	  Timer _timer;
	  bool _SDOpen;
};

#endif
