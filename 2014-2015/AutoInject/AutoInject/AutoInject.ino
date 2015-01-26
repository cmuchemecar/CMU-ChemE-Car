#include <Servo.h>

Servo servo;
int default_angle = -1;//INSERT_DEFAULT_ANGLE_HERE;
int mLConvertFactor = -1; // CENTIMETERS THE SYRINGE MOVES  PER ML INJECTED

void moveToDefault()
{
 servo.write(default_angle);
}

/* inject -  moves servo to push syringe down to inject
 *   given the number of mLs to inject, calculates the angle needed
 * by the servo to move that far and moves the servo accordingly
 *
 * rack/pinion specs - for 12-tooth gear:
 *  .1315 inches per tooth
 *  30 degrees per tooth
 *  ***    1 degree <--> 0.011133 cm  ***
 *  
 */
void inject(int mLs)
{
  // (1 degree / .011133 cm) * (X cm / mL injected) = X degrees / mL injected
  int angle = (.011133) / mlConvertFactor;
  servo.write(angle);
}

void setup()
{
 Serial.begin(9600);
 servo.attach(-1);  // INSERT SERVO PIN NUMBER HER
 
}

void loop()
{
 
  
}
