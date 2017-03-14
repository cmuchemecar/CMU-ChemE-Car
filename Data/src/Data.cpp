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
Sensor DataClass::sensor(String name, byte pin) {
  return Sensor(name, pin);
}

void DataClass::display(Sensor* sensor, int timeDec,
  int sensorDec) {
  Serial.println(DataLine(sensor->name,
    FloatToString(currentTime(), timeDec),
	FloatToString(sensor->readValue(), sensorDec)));
}

void DataClass::display(Sensor* sensor, Timer timer, int timeDec,
  int sensorDec) {
  Serial.println(DataLine(sensor->name,
    FloatToString(timer.duration(), timeDec),
	FloatToString(sensor->readValue(), sensorDec)));
}

void DataClass::sendBluetooth(Sensor* sensor, int timeDec, int sensorDec) {
  _signalBluetooth();
  Serial.println(DataLine(sensor->name,
    FloatToString(currentTime(), timeDec),
	FloatToString(sensor->readValue(), sensorDec)));
}

void DataClass::sendBluetooth(Sensor* sensor, Timer timer, int timeDec,
  int sensorDec) {
  _signalBluetooth();
  Serial.println(DataLine(sensor->name,
    FloatToString(timer.duration(), timeDec),
	FloatToString(sensor->readValue(), sensorDec)));
}

void DataClass::sendSD(Sensor* sensor, int timeDec, int sensorDec) {
  String filename = _filenameForSD(sensor->name);
  char buf[filename.length()+1];
  filename.toCharArray(buf, filename.length()+1);

  File sensorFile = SD.open(buf, FILE_WRITE);

  if (!sensor->SDOpen) {
    sensor->SDOpen = true;
    sensorFile.println("---");
	sensorFile.println("Time,Value");
  }

  sensorFile.println(FloatToString(currentTime(), timeDec)
    + "," + FloatToString(sensor->readValue(), sensorDec));
  sensorFile.close();
}

void DataClass::sendSD(Sensor* sensor, Timer timer, int timeDec,
  int sensorDec) {
  String filename = _filenameForSD(sensor->name);
  char buf[filename.length()+1];
  filename.toCharArray(buf, filename.length()+1);

  File sensorFile = SD.open(buf, FILE_WRITE);

  if (!sensor->SDOpen) {
    sensor->SDOpen = true;
    sensorFile.println("---");
	sensorFile.println("Time,Value");
  }

  sensorFile.println(FloatToString(timer.duration(), timeDec)
    + "," + FloatToString(sensor->readValue(), sensorDec));
  sensorFile.close();
}

/** VoltageSensor **/
VoltageSensor DataClass::voltageSensor(
  String name, byte pin, float R1, float R2) {
  return VoltageSensor(name, pin, R1, R2);
}

/** TemperatureSensor **/
TemperatureSensor DataClass::temperatureSensor(
  String name, byte pin, int mode) {
  return TemperatureSensor(name, pin, mode);
}

/** HallEffectSensor **/
HallEffectSensor DataClass::hallEffectSensor(
    String name, byte pin) {
    return HallEffectSensor(name, pin);
}

/** PhotoSensor **/
PhotoSensor DataClass::photoSensor(
    String name, byte pin, float R) {
	return PhotoSensor(name, pin, R);
}



