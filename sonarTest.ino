/*
  Sonar Test
  ELECTRONICS
  (c) 2018 nigel5
 */

 #include <NewPing.h>

 #include "NewPing.h"
 #include <Servo.h>
 
 // Setup sensor and standard servo
 
 #define TRIG_PIN 4
 #define ECHO_PIN 2
 #define MINIMUM_DISTANCE 20
 #define MAXIMUM_DISTANCE 250
 
 int midservoCenterAngle = 90;
 int midservoRightAngle = 0;
 int midservoLeftAngle = 180;
 
 Servo midservo;
 
 NewPing sonar(TRIG_PIN, ECHO_PIN, MAXIMUM_DISTANCE);
  void setup() {
   Serial.begin(9600);
   
   midservo.attach(5);
   midservo.write(midservoCenterAngle);
 }
 
  void loop() {
   float ping1 = sonar.ping_cm();
   
   if (ping1 != 0 && ping1 < MINIMUM_DISTANCE) {
     Serial.println(ping1);
     Serial.println("OBS");
   }
 }
