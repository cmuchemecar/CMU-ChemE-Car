#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <Arduino.h>
#include "Utility.h"
#include "Timer.h"

class Measurement {

  friend class DataClass;

  public:
    Measurement(String name, float (*measureValue)(), Timer timer);
    float getValue();
    void update();
    bool updated();
    void reset();
    void print(int dec = DEFAULTDEC);
	  void println(int dec = DEFAULTDEC);

  private:
    float (*_measureValue)();

  	String _name;
	  Timer _timer;
	  bool _SDOpen;
    float _value;
    float _time;
    bool _updated;
};

#endif
