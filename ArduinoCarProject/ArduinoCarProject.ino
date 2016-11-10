/** Arduino Car System: main file
 * Version 4.0 BETA
 * Tjerk Reintsema
 */

/** This is the main file for the Arduino Car System. Here, behaviour of the sensors and such is defined, and the main setup
 *  and loop functions of the Arduino are defined. Functions which allow easy control of the motors and data acquisition of the
 *  sensors are also provided.
 *  This file generally only needs to be edited when the hardware of the car is changed (e.g. adding new sensors) or when 
 *  completely new sensor/motor functions need to be defined. To change the behaviour of the car itself, edit the 
 *  controlCar.ino file. There, the functions defined in this file can be used to tell the car what to do.
 */

 /** CHANGLELOG - version 4.0 BETA (not yet tested on car)
  *  
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
#define leftIRsensor A3
#define rightIRsensor A2

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
int checkDistanceLeft() {
  return sampleVoltage(leftIRsensor);
}
int checkDistanceRight() {
  return sampleVoltage(rightIRsensor);
}


/* These functions return the reflection measured by either of the bottom light sensors.
 * The output is a value between 0 and 100, where 0 is maximum reflection and 100 is no reflection. */
int checkLineLeft() {return map(analogRead(leftLightSensor), 333, 236, 0, 100);}
int checkLineRight() {return map(analogRead(rightLightSensor), 430, 239, 0, 100);}


/* These functions allow easy control of the motors. The input is a value from -100 to 100, where 100 corresponds to max speed
 * ahead and -100 corresponds to max speed backwards. Change the values of calibrationL and calibrationR to calibrate. */
void motorLeft(int value) 
{
  int zeropointL = 95;
  if (value < 0) {
    value = map(value, -100, 0, -95, 0);
  }
  else if (value > 0) {
    value = map(value, 0, 100, 0, 85);
  }
  leftServo.write(zeropointL + constrain((value),-95,85));
}

void motorRight(int value) 
{
  int zeropointR = 95;
  if (value < 0) {
    value = map(value, -100, 0, -9, 0);
  }
  else if (value > 0) {
    value = map(value, 0, 100, 0, 11);
  }
  rightServo.write(zeropointR - constrain((value),-9,11));
}


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
  delay(700);
  motorLeft(80);
  motorRight(20);
  ignoreColor = 1;
  delay(1000);
}

void turnLeft() {
  delay(700);
  motorLeft(3);
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

void report() {
  Serial.print("red: \t");Serial.print(RED());Serial.print("\t");
  Serial.print("green: \t");Serial.print(GREEN());Serial.print("\t");
  Serial.print("blue: \t");Serial.print(BLUE());Serial.print("\t");

  Serial.print("left: \t");Serial.print(checkLineLeft());Serial.print("\t");
  Serial.print("right: \t");Serial.print(checkLineRight());Serial.print("\t");

  Serial.print("IR left: \t");Serial.print(checkDistanceLeft());Serial.print("\t");
  Serial.print("IR right: \t");Serial.print(checkDistanceRight());Serial.println("\t");
}

/////////////////////////////////////////// ARDUINO STARTUP FUNCTION ////////////////////////////////////////////

/* This function will be ran by the Arduino once at startup. */
void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

  tcs.begin();
  
  leftServo.attach(leftMotor); // configure left motor
  rightServo.attach(rightMotor); // configure right motr

  digitalWrite(leftLightSensor,HIGH); // configures left light sensor
  digitalWrite(rightLightSensor,HIGH); // configures right light sensor

  //randomSeed(analogRead(leftLightSensor)*10000);
}



////////////////////////////////////////// ARDUINO CONTINUOUS FUNCTION //////////////////////////////////////////

/* This function will be run continiuously by the Arduino after it has run the setup() function. */
void loop() {
  report();
  controlCar();
}
