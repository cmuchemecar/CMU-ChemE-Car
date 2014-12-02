/*************************************************** 
Thermocouple code - reads thermocouple data in celsius
  and stores it on SD card.

Format of the data:
temp_in_celsius, time_since_start

last update 11/18/14
****************************************************/

#include <SD.h>
#include <SPI.h>
#include <Adafruit_MAX31855.h>

// Default connection is using software SPI, but comment and uncomment one of
// the two examples below to switch between software SPI and hardware SPI:

// TIME DELAY IN MILLISECONDS
#define TIME_DELAY 30000

// Example creating a thermocouple instance with software SPI on any three
// digital IO pins.
#define DO   3
#define CS   4
#define CLK  5
Adafruit_MAX31855 thermocouple(CLK, CS, DO);
long start_time;

/* setup for SD card writing */
char filename[] = "THERMO.TXT"; // name of file to save data to
File data;

void setup() {
  Serial.begin(9600);
  
  start_time = millis();
  
  // setup of SD card
  pinMode(10, OUTPUT);

  SD.begin(10);
  
  // have a clear line separator for new runs
  data = SD.open(filename, FILE_WRITE);
  data.println("-----------------------------------------------------------");
  data.close();

  delay(500); // ensures proper setup of MAX31855
}

void SDWrite(String temperature) 
{
  data = SD.open(filename, FILE_WRITE);
  data.println(temperature + ", "+ String(millis() - start_time));
  data.close();
}

String floatPrint(float x){
  int intp = x;
  int fracp = (x - intp) * 1000;
  if(fracp < 0){
    fracp = -1 * fracp;
  }
  return (String(intp) + "." + String(fracp));
}

void loop() 
{
  float c = thermocouple.readCelsius();
  
    //String str = String(c)
  SDWrite(floatPrint(c));
 Serial.println(floatPrint(c));
 
  delay(TIME_DELAY);
}
