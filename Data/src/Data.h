/*
  Data.h - Library for general use in the DATA team for CMU ChemE-Car
  Created by Xavier Artache, February 8, 2016.
  Released into the public domain.
*/

#ifndef DATA_H
#define DATA_H

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "utility/Utility.h"
#include "utility/Timer.h"
#include "utility/Sensor.h"
#include "utility/VoltageSensor.h"
#include "utility/TemperatureSensor.h"
#include "utility/HallEffectSensor.h"
#include "utility/PhotoSensor.h"

#define DEFAULTBAUD 9600
#define MAXFILENAME 8

class DataClass {

  public:
    /* General Functions */
	void print();
	void println();
	void print(String str);
	void println(String str);
	void print(int x);
	void println(int x);
	void print(float x, int dec = DEFAULTDEC);
	void println(float x, int dec = DEFAULTDEC);
	void freeze();
	void beginSerial(int baud = DEFAULTBAUD);
	void beginTimer();
	float currentTime();
	void timePrint(int dec = DEFAULTDEC);
	void timePrintln(int dec = DEFAULTDEC);
	void startBluetooth();
	void stopBluetooth();
	void debugBluetooth(String str);
	void beginSD(int pin);


	/* Utility Wrappers */
	String floatToString(float x, int dec = DEFAULTDEC);
	String dataLine(String name, String time, String value);
	float millisToSeconds(unsigned long ms);
    unsigned long secondsToMillis(float s);
    float scale(float value, float max = V5);


	/* Timer */
	Timer timer();


	/* Sensors */

    /** Sensor **/
    Sensor sensor(String name, byte pin);
	void display(Sensor* sensor, int timeDec = DEFAULTDEC,
	  int sensorDec = DEFAULTDEC);
	void display(Sensor* sensor, Timer time, int timeDec = DEFAULTDEC,
	  int sensorDec = DEFAULTDEC);
	void sendBluetooth(Sensor* sensor, int timeDec = DEFAULTDEC,
	  int sensorDec = DEFAULTDEC);
	void sendBluetooth(Sensor* sensor, Timer time, int timeDec = DEFAULTDEC,
	  int sensorDec = DEFAULTDEC);
	void sendSD(Sensor* sensor, int timeDec = DEFAULTDEC,
	  int sensorDec = DEFAULTDEC);
	void sendSD(Sensor* sensor, Timer time, int timeDec = DEFAULTDEC,
	  int sensorDec = DEFAULTDEC);

	/** VoltageSensor **/
    VoltageSensor voltageSensor(String name, byte pin, float R1, float R2);

	/** TemperatureSensor **/
    TemperatureSensor temperatureSensor(String name, byte pin, int mode);

    /** HallEffectSensor **/
    HallEffectSensor hallEffectSensor(String name, byte pin);
	
	/** PhotoSensor **/
	PhotoSensor photoSensor(String name, byte pin, float R);

  private:
	void _signalBluetooth();
	String _filenameForSD(String name);

    Timer _timer;
};

extern DataClass Data;

#endif
