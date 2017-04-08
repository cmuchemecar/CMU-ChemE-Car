#include "Timer.h"

Timer::Timer() {
  this->_startTime = MillisToSeconds(millis());
}

float Timer::duration() {
  return MillisToSeconds(millis()) - _startTime;
}

void Timer::reset() {
  _startTime = MillisToSeconds(millis());
}

float Timer::increment() {
  float temp = duration();
  reset();
  return temp;
}

void Timer::print(int dec) {
  Serial.print(FloatToString(duration(), dec));
}

void Timer::println(int dec) {
  Serial.println(FloatToString(duration(), dec));
}

