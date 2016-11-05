/** Arduino Car System: main file
 * Version 2.2
 * Tjerk Reintsema
 * 1-11-2016
 */

/** CHANGELOG:
 * 1.0: first version created (27-10-2016)
 * 1.1: style updated, docstrings added (27-10-2016)
 * 1.2: line follow system implemented (1-11-2016)
 * 2.0: completely rewrote code (1-11-2016)
 * 2.1: fixed issues and added more documentation (1-11-2016)
 * 2.2: using #defines for pin numbers, allows more flexibility (1-11-2016)
 */

/** CONNECTIONS:
 *  A0 -> left light sensor
 *  A1 -> right light sensor
 *  A2 -> left IR sensor
 *  A3 -> right IR sensor
 *  6 -> left motor
 *  7 -> right motor
 *  8 -> horn
 *  13 -> LED
 */

/** This is the main file for the Arduino Car System. Here, behaviour of the sensors and such is defined, and the main setup
 *  and loop functions of the Arduino are defined. Functions which allow easy control of the motors and data acquisition of the
 *  sensors are also provided.
 *  This file generally only needs to be edited when the hardware of the car is changed (e.g. adding new sensors) or when 
 *  completely new sensor/motor functions need to be defined. To change the behaviour of the car itself, edit the 
 *  controlCar.ino file. There, the functions defined in this file can be used to tell the car what to do.
 */

 /* How to upload this code to the Arduino:
  *  1. Connect the Arduino to the computer
  *  2. Turn on the Arduino
  *  3. Press verify (checkmark in upper left corner), and if no errors occur, press upload (arrow in upper left corner)
  *  4. Wait until uploading is done
  *  5. Press the controlCar tab and repeat steps 3 and 4
  *  6. Turn off the Arduino and disconnect it
  *  7. Ready to go! Turn the Arduino on again and it will behave as defined in this code
  */

//////////////////////////////////////////////// INITIALIZATION /////////////////////////////////////////////////

 #include <Servo.h>
 Servo leftServo, rightServo;
 int sample;
 int calibrationL;
 int calibrationR;

 #define LED 13
 #define horn 8
 #define leftLightSensor A0
 #define rightLightSensor A1
 #define leftIRsensor A2
 #define rightIRsensor A3
 #define leftMotor 6
 #define rightMotor 7



//////////////////////////////////////////// FUNCTION DEFINITIONS //////////////////////////////////////////////

/* This function samples the voltage across the specified pin, and returns this as a float. */
float sampleVoltage(int pin) {
  int i;
  int SAMPLES = 3; // CHANGED FROM 5
  float average = 0;
  float voltage;

  for (i = 0; i < SAMPLES; i++) {
    sample = analogRead(pin);
    average += sample;
    delay(8); // CHANGED FROM 10
  }
  average /= SAMPLES;
  voltage = average;
  return voltage;
}


/* These functions allow the LED to be turned on or off. */
void LEDon() {digitalWrite(LED,HIGH);}
void LEDoff() {digitalWrite(LED,LOW);}


/* These functions return the distance measured by either of the IR sensors on the front of the car. 
 * This is a value between 3 and 40 cm - it doesn't work properly outside of this range */
int checkDistanceLeft() {return (2600.0 / sampleVoltage(leftIRsensor) - 0.148);}
int checkDistanceRight() {return (2600.0 / sampleVoltage(rightIRsensor) - 0.148);}


/* These functions return the reflection measured by either of the bottom light sensors.
 * The output is a value between 0 and 100, where 0 is maximum reflection and 100 is no reflection. */
int checkLineLeft() {return map(sampleVoltage(leftLightSensor), 0, 1023, 0, 100);}
int checkLineRight() {return map(sampleVoltage(rightLightSensor), 0, 1023, 0, 100);}


/* These functions allow easy control of the motors. The input is a value from -100 to 100, where 100 corresponds to max speed
 * ahead and -100 corresponds to max speed backwards. Change the values of calibrationL and calibrationR to calibrate. */
void motorLeft(int value) {leftServo.write(90 + constrain((value + calibrationL)/10,-10,10));}
void motorRight(int value) {rightServo.write(90 - constrain((value + calibrationR)/10,-10,10));}


/* This function sounds the horn of the car. */
void beep() {tone(8,500,500);}


/* This function feeds sensor data to the serial port. This report is visible by going to Tools->Serial Monitor, while the
 * Arduino is hooked up and running. */
void report() {
  Serial.print("DistanceLeft: \t"); Serial.print(checkDistanceLeft()); Serial.print("\t");
  Serial.print("DistanceRight: \t");Serial.print(checkDistanceRight()); Serial.print("\t");
  Serial.print("LineLeft: \t");Serial.print(checkLineLeft());Serial.print("\t");
  Serial.print("LineRight: \t");Serial.println(checkLineRight());
}



/////////////////////////////////////////// ARDUINO STARTUP FUNCTION ////////////////////////////////////////////

/* This function will be ran by the Arduino once at startup. */
void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  
  leftServo.attach(leftMotor); // configure left motor
  rightServo.attach(rightMotor); // configure right motor
  
  pinMode(LED,OUTPUT); // configure LED

  digitalWrite(leftLightSensor,HIGH); // configures left light sensor
  digitalWrite(rightLightSensor,HIGH); // configures right light sensor
}



////////////////////////////////////////// ARDUINO CONTINUOUS FUNCTION //////////////////////////////////////////

/* This function will be run continiuously by the Arduino after it has run the setup() function. */
void loop() {
  controlCar();
  report();
}
