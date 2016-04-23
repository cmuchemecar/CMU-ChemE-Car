#ifndef TIMER_H
#define TIMER_H

#include "Arduino.h"
#include "Utility.h"

class Timer {

  public:
    Timer();
	float duration();
    void reset();
	float increment();
	void print(int dec = DEFAULTDEC);
	void println(int dec = DEFAULTDEC);

  private:
    float _startTime;
};

#endif
