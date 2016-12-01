#include "Utility.h"

String FloatToString(float x, int dec){
  long intp = x;
  long fracp = (x - intp) * pow(10, dec);
  if(fracp < 0){
    fracp = -1 * fracp;
  }
  return (String(intp) + "." + String(fracp));
}

String DataLine(String name, String time, String value) {
  return name + ": " + time + ", " + value;
}

float MillisToSeconds(unsigned long ms) {
  return ms / 1000.0;
}

unsigned long SecondsToMillis(float s) {
  return s * 1000.0;
}

float Scale(float value, float max) {
  return value * (max / MAXANALOG);
}






