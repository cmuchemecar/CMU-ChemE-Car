#ifndef SERIES_H
#define SERIES_H

#include <Arduino.h>
#include "Utility.h"

class Series {

  public:
    Series(int size);
    void update(float value);
    bool ready();
    float get(int i);
    float sum();
    float sum(int num);
    float sum(int start, int num);
    float average();
    float average(int num);
    float average(int start, int num);
    float change();
    float averageChange(int num);
    void reset();
	void print(int dec = DEFAULTDEC);
	void println(int dec = DEFAULTDEC);

  private:
    int _inc(int i);
    int _dec(int i);

  	int _maxSize = 256;
  	int _size;
  	int _updates;
  	int _i;
    float* _values;
};

#endif
