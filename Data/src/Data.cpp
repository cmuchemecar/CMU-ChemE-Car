/*
  Data.cpp - Library for general use in the DATA team for CMU ChemE-Car
  Created by Xavier Artache, February 8, 2016.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Data.h"

/* General Functions */

void DataClass::print() {
  Serial.print("");
}

void DataClass::println() {
  Serial.println("");
}

void DataClass::print(String str) {
  Serial.print(str);
}

void DataClass::println(String str) {
  Serial.println(str);
}

void DataClass::print(int x) {
  Serial.print(x);
}

void DataClass::println(int x) {
  Serial.println(x);
}

void DataClass::print(float x, int dec) {
  Serial.print(FloatToString(x, dec));
}

void DataClass::println(float x, int dec) {
  Serial.println(FloatToString(x, dec));
}

void DataClass::beginSerial(int baud) {
  Serial.begin(baud); 
}

void DataClass::beginTimer() {
  _timer = Timer();
}

float DataClass::currentTime() {
  return _timer.duration();
}

void DataClass::timePrint(int dec) {
  _timer.print(dec);
}

void DataClass::timePrintln(int dec) {
  _timer.println(dec);
}

void DataClass::floatPrint(float x, int dec) {
  Serial.print(FloatToString(x, dec));
}

void DataClass::floatPrintln(float x, int dec) {
  Serial.println(FloatToString(x, dec));
}

void DataClass::_display(Sensor sensor, int timeDec, int sensorDec,
  float value) {
  Serial.println(DataLine(sensor.name,
    FloatToString(currentTime(), timeDec),
	FloatToString(value, sensorDec)));
}

void DataClass::_display(Sensor sensor, Timer timer, int timeDec,
  int sensorDec, float value) {
  Serial.println(DataLine(sensor.name,
    FloatToString(timer.duration(), timeDec),
	FloatToString(value, sensorDec)));
}


/* Utility Wrappers */

String DataClass::floatToString(float x, int dec){
  return FloatToString(x, dec);
}

String DataClass::dataLine(String name, String time, String value) {
  return DataLine(name, time, value);
}

float DataClass::millisToSeconds(unsigned long ms) {
  return MillisToSeconds(ms);
}

unsigned long DataClass::secondsToMillis(float s) {
  return SecondsToMillis(s);
}

float DataClass::scale(float value, float max) {
  return Scale(value, max);
}


/* Timer */

Timer DataClass::timer() {
  return Timer();
}


/* Sensors */

/** Sensor **/
Sensor DataClass::sensor(String name, int pin) {
  return Sensor(name, pin);
}

void DataClass::display(Sensor sensor, int timeDec, int sensorDec) {
  _display(sensor, timeDec, sensorDec, sensor.readValue());
}

void DataClass::display(Sensor sensor, Timer timer, int timeDec,
  int sensorDec) {
  _display(sensor, timer, timeDec, sensorDec, sensor.readValue());
}

/** VoltageSensor **/
VoltageSensor DataClass::voltageSensor(
  String name, int pin, float R1, float R2) {
  return VoltageSensor(name, pin, R1, R2);
}

void DataClass::display(VoltageSensor sensor, int timeDec, int sensorDec) {
  _display(sensor, timeDec, sensorDec, sensor.readValue());
}

void DataClass::display(VoltageSensor sensor, Timer timer, int timeDec,
  int sensorDec) {
  _display(sensor, timer, timeDec, sensorDec, sensor.readValue());
}


DataClass Data;





