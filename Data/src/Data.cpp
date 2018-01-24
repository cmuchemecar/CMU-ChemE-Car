/*
  Data.cpp - Library for general use in the DATA team for CMU ChemE-Car
  Created by Xavier Artache, February 8, 2016.
  Released into the public domain.
*/

#include "Data.h"
DataClass Data;

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

void DataClass::freeze() {
  while(1);
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


void DataClass::startBluetooth() {
  _signalBluetooth();
  Serial.println("START");
}

void DataClass::stopBluetooth() {
  _signalBluetooth();
  Serial.println("STOP");
}

void DataClass::debugBluetooth(String str) {
  _signalBluetooth();
  Serial.println(str);
}

void DataClass::debugBluetooth(int x) {
  _signalBluetooth();
  Serial.println(x);
}

void DataClass::debugBluetooth(float x, int dec) {
  _signalBluetooth();
  Serial.println(FloatToString(x, dec));
}

void DataClass::beginSD(int pin) {
  pinMode(pin, OUTPUT);
  SD.begin(pin);
}


/* Private Functions */
void DataClass::_signalBluetooth() {
  Serial.print("BLUETOOTH: ");
}

String DataClass::_filenameForSD(String name) {
  String filename;
  if (name.length()-1 > MAXFILENAME) {
    filename = name.substring(0, MAXFILENAME);
  }
  else {
    filename = name;
  }
  filename += ".txt";
  filename.toUpperCase();

  return filename;
}


/* Data Transfer Functions */

void DataClass::display(Sensor sensor, int timeDec,
  int valueDec) {
  Serial.println(DataLine(sensor._name,
    FloatToString(sensor._timer.duration(), timeDec),
    FloatToString(sensor.readValue(), valueDec)));
}

void DataClass::display(Actuator actuator, int timeDec,
  int valueDec) {
  Serial.println(DataLine(actuator._name,
    FloatToString(actuator._time, timeDec),
    FloatToString(actuator._value, valueDec)));
}

void DataClass::display(Measurement measurement, int timeDec,
  int valueDec) {
  Serial.println(DataLine(measurement._name,
    FloatToString(measurement._time, timeDec),
    FloatToString(measurement._value, valueDec)));
}

void DataClass::sendBluetooth(Sensor sensor, int timeDec, int valueDec) {
  _signalBluetooth();
  Serial.println(DataLine(sensor._name,
    FloatToString(sensor._timer.duration(), timeDec),
    FloatToString(sensor.readValue(), valueDec)));
}

void DataClass::sendBluetooth(Actuator actuator, int timeDec,
  int valueDec) {
  _signalBluetooth();
  Serial.println(DataLine(actuator._name,
    FloatToString(actuator._time, timeDec),
    FloatToString(actuator._value, valueDec)));
}

void DataClass::sendBluetooth(Measurement measurement, int timeDec,
  int valueDec) {
  _signalBluetooth();
  Serial.println(DataLine(measurement._name,
    FloatToString(measurement._time, timeDec),
    FloatToString(measurement._value, valueDec)));
}

void DataClass::sendSD(Sensor sensor, int timeDec, int valueDec) {
  String filename = _filenameForSD(sensor._name);
  char buf[filename.length()+1];
  filename.toCharArray(buf, filename.length()+1);

  File dataFile = SD.open(buf, FILE_WRITE);

  if (!sensor._SDOpen) {
    sensor._SDOpen = true;
    dataFile.println("---");
  dataFile.println("Time,Value");
  }

  dataFile.println(FloatToString(sensor._timer.duration(), timeDec)
    + "," + FloatToString(sensor.readValue(), valueDec));
  dataFile.close();
}

void DataClass::sendSD(Actuator actuator, int timeDec,
  int valueDec) {
  String filename = _filenameForSD(actuator._name);
  char buf[filename.length()+1];
  filename.toCharArray(buf, filename.length()+1);

  File dataFile = SD.open(buf, FILE_WRITE);

  if (!actuator._SDOpen) {
    actuator._SDOpen = true;
    dataFile.println("---");
  dataFile.println("Time,Value");
  }

  dataFile.println(FloatToString(actuator._time, timeDec)
    + "," + FloatToString(actuator._value, valueDec));
  dataFile.close();
}

void DataClass::sendSD(Measurement measurement, int timeDec,
  int valueDec) {
  String filename = _filenameForSD(measurement._name);
  char buf[filename.length()+1];
  filename.toCharArray(buf, filename.length()+1);

  File dataFile = SD.open(buf, FILE_WRITE);

  if (!measurement._SDOpen) {
    measurement._SDOpen = true;
    dataFile.println("---");
    dataFile.println("Time,Value");
  }

  dataFile.println(FloatToString(measurement._time, timeDec)
    + "," + FloatToString(measurement._value, valueDec));
  dataFile.close();
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

/* Series */
Series DataClass::series(int size) {
  return Series(size);
}

Measurement DataClass::measurement(String name,
  float (*measureValue)()) {
  return Measurement(name, measureValue, _timer);
}

Measurement DataClass::measurement(String name,
  float (*measureValue)(), Timer time) {
  return Measurement(name, measureValue, time);
}


/* Sensors */

/** Sensor **/
Sensor DataClass::sensor(String name, byte pin) {
  return Sensor(name, pin, _timer);
}

Sensor DataClass::sensor(String name, byte pin, Timer time) {
  return Sensor(name, pin, time);
}

/** VoltageSensor **/
VoltageSensor DataClass::voltageSensor(
  String name, byte pin, float R1, float R2) {
  return VoltageSensor(name, pin, _timer, R1, R2);
}

VoltageSensor DataClass::voltageSensor(
  String name, byte pin, Timer time, float R1, float R2) {
  return VoltageSensor(name, pin, time, R1, R2);
}

/** TemperatureSensor **/
TemperatureSensor DataClass::temperatureSensor(
  String name, byte pin, int mode) {
  return TemperatureSensor(name, pin, _timer, mode);
}

TemperatureSensor DataClass::temperatureSensor(
  String name, byte pin, Timer time, int mode) {
  return TemperatureSensor(name, pin, time, mode);
}

/** HallEffectSensor **/
HallEffectSensor DataClass::hallEffectSensor(
    String name, byte pin) {
    return HallEffectSensor(name, pin, _timer);
}

HallEffectSensor DataClass::hallEffectSensor(
    String name, byte pin, Timer time) {
    return HallEffectSensor(name, pin, time);
}

/** WheelSensor **/
WheelSensor DataClass::wheelSensor(
    String name, byte pin, float wheelRadius, int numMagnets) {
    return WheelSensor(name, pin, _timer, wheelRadius, numMagnets); 
}

WheelSensor DataClass::wheelSensor(
    String name, byte pin, Timer time, float wheelRadius, int numMagnets) {
    return WheelSensor(name, pin, time, wheelRadius, numMagnets); 
}

/** PhotoSensor **/
PhotoSensor DataClass::photoSensor(
    String name, byte pin, float R) {
	return PhotoSensor(name, pin, _timer, R);
}

PhotoSensor DataClass::photoSensor(
    String name, byte pin, Timer time, float R) {
  return PhotoSensor(name, pin, time, R);
}

/** SwitchSensor **/
SwitchSensor DataClass::switchSensor(
    String name, byte pin) {
  return SwitchSensor(name, pin, _timer);
}

SwitchSensor DataClass::switchSensor(
    String name, byte pin, Timer time) {
  return SwitchSensor(name, pin, time);
}

/* Actuator */

/** Actuator **/
Actuator DataClass::actuator(
  String name, byte pin) {
  return Actuator(name, pin, _timer);
}

Actuator DataClass::actuator(
  String name, byte pin, Timer time) {
  return Actuator(name, pin, time);
}

/** MotorActuator **/
MotorActuator DataClass::motorActuator(
  String name, byte pin) {
  return MotorActuator(name, pin, _timer);
}

MotorActuator DataClass::motorActuator(
  String name, byte pin, Timer time) {
  return MotorActuator(name, pin, time);
}

