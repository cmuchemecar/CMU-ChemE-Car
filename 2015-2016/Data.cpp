/*
  Data.cpp - Library for general use in the DATA team for CMU Cheme-Car
  Created by Xavier Artache, February 8, 2016.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Data.h"

/*
Data::Data(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}
*/

void Data::dot()
{
  digitalWrite(_pin, HIGH);
  delay(250);
  digitalWrite(_pin, LOW);
  delay(250);  
}
