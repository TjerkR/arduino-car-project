/** Arduino Car System: motor testing
 */

//////////////////////////////////////////////// INITIALIZATION /////////////////////////////////////////////////

#include <Servo.h>
Servo leftServo, rightServo;

#define leftMotor 10 // needs to be PWM port
#define rightMotor 9 // idem



//////////////////////////////////////////// FUNCTION DEFINITIONS //////////////////////////////////////////////

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



/////////////////////////////////////////// ARDUINO STARTUP FUNCTION ////////////////////////////////////////////

/* This function will be ran by the Arduino once at startup. */
void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  
  leftServo.attach(leftMotor); // configure left motor
  rightServo.attach(rightMotor); // configure right motor

  motorLeft(0);
  motorRight(0);
}



////////////////////////////////////////// ARDUINO CONTINUOUS FUNCTION //////////////////////////////////////////

/* This function will be run continiuously by the Arduino after it has run the setup() function. */
void loop() {

  char c = Serial.read();
  if (c == 'w') {
    motorLeft(80);
    motorRight(80);
  }
  if (c == 'a') {
    motorLeft(3);
    motorRight(100);
  }
  if (c == 's') {
    motorLeft(-50);
    motorRight(-50);
  }
  if (c == 'd') {
    motorLeft(80);
    motorRight(20);
  }
  if (c == 'x') {
    motorLeft(0);
    motorRight(0);
  }
}
