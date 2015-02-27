
#include <SD.h>

/* setup for SD card writing */
char filename[] = "TEST.TXT"; // name of file to save data to
File data;
String s = "hello";

void setup() {  
  // setup of SD card
  pinMode(10, OUTPUT);
  SD.begin(10);
  
  // have a clear line separator for new runs
  SDWrite("-----------------------------------------------------------");
}

void loop() 
{
  SDWrite(s);
  delay(1000);
}


void SDWrite(String s) 
{
  data = SD.open(filename, FILE_WRITE);
  data.println(s);
  data.close();
}
