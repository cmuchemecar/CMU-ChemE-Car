#include <Servo.h>
Servo Motor; 
 
const int MF = 20;  // angle that moves motor forward
const int MB = 138; // angle that moves motor backward
const int MS = 91; // angle that stops the motor
 
void setup()
{
 // The white pin of the VEX motor controller 29
 // connects to pin 5 (or any other PWM pin)
 Motor.attach(5);
}
 
void loop() 
{
  Motor.write(MF); // move forward
  delay(1000);     // 0.5 mL
//  delay(100);  // 1 mL
 
  Motor.write(MS); // stop motor
  delay(1000);  
 
  Motor.write(MB); // move backward
  delay(1000);
//  delay(100);
  
  Motor.write(MS); // stop motor
  delay(1000);   
}


