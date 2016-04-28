#ifndef UTILITY_H
#define UTILITY_H

#include <Arduino.h>

#define DEFAULTDEC 3
#define MAXANALOG 1023.0
#define V5 5.0
#define V3.3 3.3

String FloatToString(float x, int dec = DEFAULTDEC);
String DataLine(String name, String time, String value);
float MillisToSeconds(unsigned long ms);
unsigned long SecondsToMillis(float s);
float Scale(float value, float max = V5);

#endif
