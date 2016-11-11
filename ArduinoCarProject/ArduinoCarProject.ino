/** Arduino Car System: main file
 * Version 4.0
 * Tjerk Reintsema
 */

/** This is the main file for the Arduino Car System. Here, behaviour of the sensors and such is defined, and the main setup
 *  and loop functions of the Arduino are defined. Functions which allow easy control of the motors and data acquisition of the
 *  sensors are also provided.
 *  This file generally only needs to be edited when the hardware of the car is changed (e.g. adding new sensors) or when 
 *  completely new sensor/motor functions need to be defined. To change the behaviour of the car itself, edit the 
 *  controlCar.ino file. There, the functions defined in this file can be used to tell the car what to do.
 */

//////////////////////////////////////////////// INITIALIZATION /////////////////////////////////////////////////

#include <Servo.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725();
/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

Servo leftServo, rightServo;

int ignoreColor;
int count = 1;
int trafficLight = 0;
long randNumber;
int multiplier = 45; 
int waitCount = 0;

#define leftLightSensor A0
#define rightLightSensor A1
#define leftIRsensor A3
#define rightIRsensor A2

#define leftMotor 10
#define rightMotor 9



//////////////////////////////////////////// FUNCTION DEFINITIONS //////////////////////////////////////////////

/* This function returns the average of the last <samples> readings of the voltage over <pin>. */
float sampleVoltage(int pin, int samples) {
  float average = 0;
  int i;
 
  for (i = 0; i < samples; i++) {
    average += analogRead(pin);
    delay(8);
  }
 
  return average/samples;
}


/* These functions return a value proportional tot the distance measured by the IR sensors. */
int checkDistanceLeft() {
  return sampleVoltage(leftIRsensor,3);
}
int checkDistanceRight() {
  return sampleVoltage(rightIRsensor,3);
}


/* These functions return the reflection measured by either of the bottom light sensors.
 * The output is a value between 0 and 100, where 0 is maximum reflection and 100 is no reflection. */
int checkLineLeft() {return map(analogRead(leftLightSensor), 333, 236, 0, 100);}
int checkLineRight() {return map(analogRead(rightLightSensor), 430, 239, 0, 100);}


/* These functions allow easy control of the motors. The input is a value from -100 to 100, where 100 corresponds to max speed
 * ahead and -100 corresponds to max speed backwards. */
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
  ignoreColor = 1;
  
  delay(700);
  motorLeft(100);
  motorRight(15);
  
  ignoreColor = 0;
  
  delay(750);
}


void turnLeft() {
  ignoreColor = 1;
  
  delay(700);
  motorLeft(3);
  motorRight(100);
  
  ignoreColor = 0;
  
  delay(750);
}


void goStraight() {
  motorLeft(80);
  motorRight(80);
  ignoreColor = 1;
  if ( (RED() > 50) || 
       ((RED() < 35) && (GREEN() > 40) && (BLUE() < 27)) || 
       ((RED() < 30) && (GREEN() < 37) && (BLUE() > 35)) || 
       ((RED() > 35) && (GREEN() < 28) && (BLUE() < 20)) || 
       ((RED() > 35) && (GREEN() > 35) && (BLUE() < 25)) ) {
  ignoreColor = 0;
  delay(250);
  }
}


void stopCar() {
  motorLeft(0);
  motorRight(0);
}

/* Function used to see what the sensors are reading, for debugging purposes. */
void report() {
  Serial.print("\t red: \t");Serial.print(RED());Serial.print("\t");
  Serial.print("green: \t");Serial.print(GREEN());Serial.print("\t");
  Serial.print("blue: \t");Serial.print(BLUE());Serial.print("\t");

  Serial.print("ignoreColor: \t");Serial.print(ignoreColor);Serial.print("\t");

  Serial.print("trafficLight: \t");Serial.print(trafficLight);Serial.print("\t");

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

  randomSeed(analogRead(leftLightSensor)*10000);
}



////////////////////////////////////////// ARDUINO CONTINUOUS FUNCTION //////////////////////////////////////////

/* This function will be run continiuously by the Arduino after it has run the setup() function. */
void loop() {
  report();
  controlCar();
  
  // traffic light signal
  if (waitCount != 0) {
    count += waitCount;
    waitCount = 0;
  }
  
  if (count >= 4*multiplier) {
    count = 0;
    trafficLight = 0;
  }
  else if (count > 2*multiplier) {
    trafficLight = 0; 
  }
  else {
    trafficLight = 1;
  }
  count++;
  
}
