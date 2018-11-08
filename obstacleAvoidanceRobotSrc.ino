/*
  Scanning Obstacle Avoidance Robot
  ELECTRONICS
  (c) 2018 nigel5
 */
 
 #include <NewPing.h>
 #include <Servo.h>
 
 // Setup sensor and standard servo
 
 #define TRIG_PIN 4
 #define ECHO_PIN 2
 #define MINIMUM_DISTANCE 15
 #define MAXIMUM_DISTANCE 250
 
 #define MAX_SCAN_RIGHT 15
 #define MAX_SCAN_LEFT 165
 
 int midservoCenterAngle = 90;
 int midservoRightAngle = 0;
 int midservoLeftAngle = 180;
 
 Servo midservo;
 
 NewPing sonar(TRIG_PIN, ECHO_PIN, MAXIMUM_DISTANCE);
 
 // Setup continuous servos (wheels)
 Servo servoRight;
 Servo servoLeft;
 int delayTime = 100;
 int adRight = 59;
 int adLeft = 0;
 
 // Scanning variables
 boolean pauseScanner = false;
 int scanningSpeed = 1;
 int currentAngle = midservoCenterAngle;
 
 boolean leftObs;
 boolean rightObs;
 
 void setup() {   
   Serial.begin(9600);
   // Attach and centre the middle servo
   midservo.attach(5);
   midservo.write(midservoCenterAngle);
   
   // Attach wheel servos
   servoRight.attach(12);
   servoLeft.attach(13);
 }
 
 void loop() {
   go_forward();
   
   float ping1 = sonar.ping_cm();
    
   // Scanning and adjustment
   if (!pauseScanner) {
     // Reached max right or left angle, start scanning opposite way
     if ((currentAngle <= MAX_SCAN_RIGHT + 10 && scanningSpeed < 0) || (currentAngle >= MAX_SCAN_LEFT - 10 && scanningSpeed > 0)) {
       scanningSpeed *= -1;
     }
     midservo.write(currentAngle + scanningSpeed);
     currentAngle += scanningSpeed;
     delay(10);
     
     // Veer right (approaching left wall)
     if (ping1 != 0 && ping1 <= MINIMUM_DISTANCE + 20 && 90 < currentAngle < 180) {
       adRight += 10;
       Serial.println("APPR OBS LEFT");
     }
     
     // Veer left (approaching right wall)
     else if (ping1 != 0 && ping1 <= MINIMUM_DISTANCE + 20 && 0 < currentAngle < 90 ) {
       adRight -= 10;
       Serial.println("APPR OBS RIGHT");
     }
   }
   if (ping1 != 0 && ping1 <= MINIMUM_DISTANCE) {
     pauseScanner = true;
     brake();
     delay(100);
     
     // Confirm that obstacle is there. If true, check both sides
     if (go_look_forward()) {
       leftObs = go_look_left();
       rightObs = go_look_right();
            Serial.println("OBS");

       if (leftObs && !rightObs) {
         // Right side clear
         delay(15);
         turn_back_right(); 
       }
       else if (!leftObs && rightObs) {
         // Left side clear
         delay(15);
         turn_back_left();
       }
       else {
         // Both sides clear
         delay(15);
         turn_around();
       }
       // Center servo
       go_look_forward();
       go_forward();
       ping1 = 0;
     }
     else {
       go_forward();
       ping1 = 0;
     }
     // Restart scanning
     pauseScanner = false;
   }
 }
 
 /*
  * This function causes the robot to check for any obstacles on the left side.
  * If an obstacle is present, then it will return true. Otherwise, it will return false.
  */
 boolean go_look_left() {
   midservo.write(midservoLeftAngle);
   delay(450);
   float ping1 = sonar.ping_cm();
   delay(20);
   
   if (ping1 != 0 && ping1 <= MINIMUM_DISTANCE) {
     return true;
   }
   
   return false;
 }
 
 /*
  * This function causes the robot to check for any obstacles on the right side.
  * If an obstacle is present, then it will return true. Otherwise, it will return false.
  */
 boolean go_look_right() {
   midservo.write(midservoRightAngle);
   delay(450);
   
   float ping1 = sonar.ping_cm();
   delay(20);
   
   if (ping1 != 0 && ping1 <= MINIMUM_DISTANCE) {
     return true;
   }
   
   return false;
 }
 
 /*
  * This function causes the robot to check for any obstacles in front of it.
  * If an obstacle is present, then it will return true. Otherwise, it will return false.
  */
 boolean go_look_forward() {
   midservo.write(midservoCenterAngle);
   delay(450);
   
   float ping1 = sonar.ping_cm();
   
   if (ping1 != 0 && ping1 <= MINIMUM_DISTANCE) {
     return true;
   }
   
   return false;
 }
 
 /*
  * This function causes the robot to move forward.
  */
 void go_forward() {
   servoRight.writeMicroseconds(800 + adRight);
   servoLeft.writeMicroseconds(2200 + adLeft);
 }
 
 /*
  * This function causes the robot to move backward.
  */
 void go_backward() {
   servoRight.writeMicroseconds(2200 + adRight);
   servoLeft.writeMicroseconds(800 + adLeft);
 }
 
 /*
  * This function causes the robot to turn left.
  */
 void turn_back_left() {
  servoRight.writeMicroseconds(800);
  servoLeft.writeMicroseconds(800);
  delay(540);
}
 
 /*
  * This function causes the robot to turn right.
  */
 void turn_back_right() {
  servoRight.writeMicroseconds(2200);
  servoLeft.writeMicroseconds(2200);
  delay(540);
}
 
 /*
  * This function causes the robot to stop.
  */
 void brake() {
   servoRight.writeMicroseconds(1500);
   servoLeft.writeMicroseconds(1500);
   delay(500);
   servoRight.detach();
   servoLeft.detach();
   delay(200);
   servoRight.attach(12);
   servoLeft.attach(13);
 }
 
 /*
  * This function causes the robot to turn around by first moving backwards, then turning right.
  */
 void turn_around() {
   // backup, and then turn around
   go_backward();
   delay(150);
   turn_back_right();
   delay(5);
 }
