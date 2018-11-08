# obstacleAvoidanceRobot
This is an obstacle avoidance robot made with Arduino. The robot detects obstacles in its path by using the HC-SR04 Ultrasonic sensor. A servo motor allows the sensor to "scan" the area in front of it (~180°).
The robot generally will travel in a straight line. When an obstacle is detected, the robot will make a decision on whether to turn around, or continue travelling if the obstacle has cleared.

The robot can detect obstacles in front, left, and right by it's sweeping scanner. Therefore, obstacle behind will not be detected, and it is possible to "box in" the robot.

## Requirements

#### External Libraries
- NewPing 1.8

#### Calibration of the servos
For maximum performance, the servos must be calibrating according to the manufacturers specifications before using this robot. Typically, this involves adjusting the potentiometer such that the motor will not spin at a pulse of 1500uS.

#### BOM
- Arduino Uno Rev3 (1)
- HC-SR04 Ultrasonic Sensor (1)
- Parallax Servo Motor #900-00008 (continuous) (2)
- Standard Servo Motor TowerPro SG90 (1)
- 6 AA Battery Holder Case with wire (1)
- 2WD Robot Chassis Kit with Ball Caster (1)

## Note on Battery Voltage
Lower battery voltage than normal (1.5V) will affect behavior the robot, and may cause unexpected movements. For example, it may not turn enough to clear the obstacle.

Symptoms of low battery include the robot not travelling straight, not clearing the obstacle, or "stuttering" start-stop movement.

## Known Issues
- It is very easy to trap the robot. Commonly, it will be in a deadlock on whether to turn or to continue forward.