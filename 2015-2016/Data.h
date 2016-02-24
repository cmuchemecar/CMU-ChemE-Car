/*
  Data.h - Library for general use in the DATA team for CMU Cheme-Car
  Created by Xavier Artache, February 8, 2016.
  Released into the public domain.
*/
#ifndef Data_h
#define Data_h

#include "Arduino.h"

class Data
{
  public:
    Data(int pin);
    void dot();
    void dash();
  private:
    int _pin;
};

#endif