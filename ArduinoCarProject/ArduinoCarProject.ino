/** Arduino Car System: main file
 * Version 3.1 BETA
 * Tjerk Reintsema
 */

/** This is the main file for the Arduino Car System. Here, behaviour of the sensors and such is defined, and the main setup
 *  and loop functions of the Arduino are defined. Functions which allow easy control of the motors and data acquisition of the
 *  sensors are also provided.
 *  This file generally only needs to be edited when the hardware of the car is changed (e.g. adding new sensors) or when 
 *  completely new sensor/motor functions need to be defined. To change the behaviour of the car itself, edit the 
 *  controlCar.ino file. There, the functions defined in this file can be used to tell the car what to do.
 */

 /** CHANGLELOG - version 3.1 BETA (not yet tested on car)
  *  new functions:
  *  - Added functions turnLeft(), turnRight() for turning the car left/right for 1 second and ignoring the next color code
  *  - Added a function goStraigh() for ignoring the next color code
  *  - Added a function stopCar() to stop the car until directed otherwise
  *  - Added a function trafficLight() to check if the traffic light is red (1) or green (0), both have equal chance
  *  new behaviour:
  *  - The car can now handle T-junctions and crossroads (if they are marked as such with color codes)
  *  - Added functionality for checking traffic lights at crossroads, which have a 50 percent chance of being on or off
  *  other:
  *  - Added random seed generator via analogRead(leftLightSensor*1000)
  */

//////////////////////////////////////////////// INITIALIZATION /////////////////////////////////////////////////

#include <Servo.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
Adafruit_TCS34725 tcs = Adafruit_TCS34725();
/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */
Servo leftServo, rightServo;
int calibrationL;
int calibrationR;
int ignoreColor;
long randNumber;

#define leftLightSensor A0
#define rightLightSensor A1
#define leftIRsensor A2
#define rightIRsensor A3
#define SDA A4
#define SCL A5

#define leftMotor 10 // needs to be PWM port
#define rightMotor 9 // idem



//////////////////////////////////////////// FUNCTION DEFINITIONS //////////////////////////////////////////////

/* This function samples the voltage across the specified pin, and returns this as a float. */
float sampleVoltage(int pin) {
  int samples = 3;
  float average = 0;

  int i;
  for (i = 0; i < samples; i++) {
    average += analogRead(pin);
    delay(8);
  }
  average /= samples;
  return average;
}


/* These functions return the distance measured by either of the IR sensors on the front of the car. 
 * This is a value between 4 and 80 cm - it doesn't work properly outside of this range */
int checkDistanceLeft() {return (2600.0 / sampleVoltage(leftIRsensor) - 0.15);}
int checkDistanceRight() {return (2600.0 / sampleVoltage(rightIRsensor) - 0.15);}


/* These functions return the reflection measured by either of the bottom light sensors.
 * The output is a value between 0 and 100, where 0 is maximum reflection and 100 is no reflection. */
int checkLineLeft() {return map(analogRead(leftLightSensor), 0, 1023, 0, 100);}
int checkLineRight() {return map(analogRead(rightLightSensor), 0, 1023, 0, 100);}


/* These functions allow easy control of the motors. The input is a value from -100 to 100, where 100 corresponds to max speed
 * ahead and -100 corresponds to max speed backwards. Change the values of calibrationL and calibrationR to calibrate. */
void motorLeft(int value) {leftServo.write(90 + constrain((value + calibrationL)/10,-10,10));}
void motorRight(int value) {rightServo.write(90 - constrain((value + calibrationR)/10,-10,10));}


/* Color sensor functions. RED() returns the percentage of red light of the total light. */
float RED() {
  uint16_t r, g, b, c;
  float total, part;
  tcs.getRawData(&r, &g, &b, &c);
  total = r + g + b;
  part = r / total * 100;
  return part;
}
float GREEN() {
  uint16_t r, g, b, c;
  float total, part;
  tcs.getRawData(&r, &g, &b, &c);
  total = r + g + b;
  part = g / total * 100;
  return part;
}
float BLUE() {
  uint16_t r, g, b, c;
  float total, part;
  tcs.getRawData(&r, &g, &b, &c);
  total = r + g + b;
  part = b / total * 100;
  return part;
}

/* Functions for turning the car left, right or directing it straight ahead for a little while. */
void turnRight() {
  motorLeft(100);
  motorRight(20);
  ignoreColor = 1;
  delay(1000);
}

void turnLeft() {
  motorLeft(20);
  motorRight(100);
  ignoreColor = 1;
  delay(1000);
}

void goStraight() {
  ignoreColor = 1;
  delay(1000);
}

void stopCar() {
  motorLeft(0);
  motorRight(0);
}

/* Function to check if the stoplight is on or not. On == 1, off == 0. */
int trafficLight() {
  return random(2); // TODO: replace this with a controllable signal eventually
}

/////////////////////////////////////////// ARDUINO STARTUP FUNCTION ////////////////////////////////////////////

/* This function will be ran by the Arduino once at startup. */
void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

  tcs.begin();
  
  leftServo.attach(leftMotor); // configure left motor
  rightServo.attach(rightMotor); // configure right motor

  digitalWrite(leftLightSensor,HIGH); // configures left light sensor
  digitalWrite(rightLightSensor,HIGH); // configures right light sensor

  randomSeed(analogRead(leftLightSensor)*10000);
}



////////////////////////////////////////// ARDUINO CONTINUOUS FUNCTION //////////////////////////////////////////

/* This function will be run continiuously by the Arduino after it has run the setup() function. */
void loop() {
  controlCar();
}
