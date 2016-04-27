/*
  Data.h - Library for general use in the DATA team for CMU ChemE-Car
  Created by Xavier Artache, February 8, 2016.
  Released into the public domain.
*/

#ifndef DATA_H
#define DATA_H

#include "Arduino.h"
#include "utility/Utility.h"
#include "utility/Timer.h"
#include "utility/Sensor.h"
#include "utility/VoltageSensor.h"

#define DEFAULTBAUD 9600

class DataClass {
  
  public:
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
	void floatPrint(float x, int dec = DEFAULTDEC);
	void floatPrintln(float x, int dec = DEFAULTDEC);
	void startBluetooth();
	void stopBluetooth();
	void debugBluetooth(String str);
	  
	String floatToString(float x, int dec = DEFAULTDEC);
	String dataLine(String name, String time, String value);
	float millisToSeconds(unsigned long ms);
    unsigned long secondsToMillis(float s);
    float scale(float value, float max = V5);
	
	Timer timer();
	
	
    Sensor sensor(String name, int pin);
	void display(Sensor sensor, int timeDec = DEFAULTDEC,
	  int sensorDec = DEFAULTDEC);
	void display(Sensor sensor, Timer time, int timeDec = DEFAULTDEC,
	  int sensorDec = DEFAULTDEC);
	void sendBluetooth(Sensor sensor, int timeDec = DEFAULTDEC,
	  int sensorDec = DEFAULTDEC);
	void sendBluetooth(Sensor sensor, Timer time, int timeDec = DEFAULTDEC,
	  int sensorDec = DEFAULTDEC); 
	  
    VoltageSensor voltageSensor(String name, int pin, float R1, float R2);
	void display(VoltageSensor sensor, int timeDec = DEFAULTDEC,
	  int sensorDec = DEFAULTDEC);
	void display(VoltageSensor sensor, Timer time, int timeDec = DEFAULTDEC,
	  int sensorDec = DEFAULTDEC);
	void sendBluetooth(VoltageSensor sensor, int timeDec = DEFAULTDEC,
	  int sensorDec = DEFAULTDEC);
	void sendBluetooth(VoltageSensor sensor, Timer time, int timeDec = DEFAULTDEC,
	  int sensorDec = DEFAULTDEC); 
    
  private:
    void _display(Sensor sensor, int timeDec, int sensorDec, float value);
    void _display(Sensor sensor, Timer timer, int timeDec, int sensorDec,
	  float value);
	void _signalBluetooth();
	void _sendBluetooth(Sensor sensor, int timeDec, int sensorDec, float value);
    void _sendBluetooth(Sensor sensor, Timer timer, int timeDec, int sensorDec,
	  float value);
  
    Timer _timer;
};

extern DataClass Data;

#endif
