 /*
  Servo Calibration (Centering)
  ELECTRONICS
  (c) 2018 nigel5
 */
#include <Servo.h>

Servo servoLeft;
Servo servoRight;

void setup() {
  servoLeft.attach(13);
  servoRight.attach(12);
  
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}
