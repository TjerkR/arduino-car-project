/** Arduino Car System: motor testing
 */

//////////////////////////////////////////////// INITIALIZATION /////////////////////////////////////////////////

#include <Servo.h>
Servo leftServo, rightServo;
int calibrationL;
int calibrationR;


#define leftMotor 9 // needs to be PWM port
#define rightMotor 10 // idem



//////////////////////////////////////////// FUNCTION DEFINITIONS //////////////////////////////////////////////

/* These functions allow easy control of the motors. The input is a value from -100 to 100, where 100 corresponds to max speed
 * ahead and -100 corresponds to max speed backwards. Change the values of calibrationL and calibrationR to calibrate. */
void motorLeft(int value) {leftServo.write(90 + constrain((value + calibrationL)/10,-10,10));}
void motorRight(int value) {rightServo.write(90 - constrain((value + calibrationR)/10,-10,10));}


/////////////////////////////////////////// ARDUINO STARTUP FUNCTION ////////////////////////////////////////////

/* This function will be ran by the Arduino once at startup. */
void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  
  leftServo.attach(leftMotor); // configure left motor
  rightServo.attach(rightMotor); // configure right motor
}



////////////////////////////////////////// ARDUINO CONTINUOUS FUNCTION //////////////////////////////////////////

/* This function will be run continiuously by the Arduino after it has run the setup() function. */
void loop() {
  
  calibrationL = 0;
  calibrationR = 0;

  char c = Serial.read();
  if (c == 'w') {
    motorLeft(100);
    motorRight(100);
  }
  if (c == 's') {
    motorLeft(-100);
    motorRight(-100);
  }
  if (c == 'a') {
    motorLeft(0);
    motorRight(100);
  }
    if (c == 'd') {     motorLeft(100);
    motorRight(0);
  }
}
