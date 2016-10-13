// Testing (use analog pin for now)
#include <Data.h>

#define HALLPIN A0
#define HALLTHRESHOLD 20  // Off is usually 0-2, on is usually 117-119 raw

void setup() {
  pinMode(HALLPIN, INPUT);
  Data.beginSerial();
}

void loop() {
  int hallRaw = analogRead(HALLPIN);
  bool magnetNear = (hallRaw < HALLTHRESHOLD);
  Serial.println(hallRaw);
}
