/** Arduino Car System: motor testing
 */

//////////////////////////////////////////////// INITIALIZATION /////////////////////////////////////////////////

#include <Servo.h>
Servo leftServo, rightServo;
int calibrationL;
int calibrationR;


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

/// TESTS!
/*
void motorLeft(int value) 
{
  leftServo.write(90 + constrain( (0 + 50)/10,-10,10  )       );   --> 95 = stop
}


void motorRight(int value) 
{
  rightServo.write(90 - constrain((0 + -50)/10,-10,10)); ---> 85 = stop
}
*/

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
  
  //calibrationL = 50; // 50 for stand still, -50 R
  //calibrationR = -50;

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


  /*
  char c = Serial.read();
  if (c == 'x') {
  leftServo.write(90      + 5);
  rightServo.write(90     + 5);
  }

  if (c == 'w') {
  leftServo.write(180     + 0); //35
  rightServo.write(0      + 84);   //5
  }

  if (c == 's') {
  leftServo.write(0       + 0); //25
  rightServo.write(180    - 76);   //5
  }
  */

  /*
  char c = Serial.read();
  if (c == 'w') {
    motorLeft(80);
    motorRight(80);
  }
  if (c == 's') {
    motorLeft(-80);
    motorRight(-80);
  }
  if (c == 'a') {
    motorLeft(20);
    motorRight(80);
  }
  if (c == 'd') {     
    motorLeft(80);
    motorRight(20);
  }
  if (c == 'x') {
    motorLeft(0);
    motorRight(0);
  }

  if (c == 't') {
    leftServo.write(180);
    rightServo.write(0);
  }
  */
}
