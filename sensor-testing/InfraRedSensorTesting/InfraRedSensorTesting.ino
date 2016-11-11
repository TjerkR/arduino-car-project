/** Arduino Car System: infrared sensor testing
 */

//////////////////////////////////////////////// INITIALIZATION /////////////////////////////////////////////////

int sample;
#define leftIRsensor A2
#define rightIRsensor A3



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



/* These functions return the distance measured by either of the IR sensors on the front of the car. 
 * This is a value between 3 and 40 cm - it doesn't work properly outside of this range */
//int checkDistanceLeft() {return (12000.0 / sampleVoltage(leftIRsensor) - 3.5);}
//int checkDistanceRight() {return (12000.0 / sampleVoltage(rightIRsensor) - 3.5);}
int checkDistanceLeft() {return sampleVoltage(leftIRsensor,3);}
int checkDistanceRight() {return sampleVoltage(rightIRsensor,3);}


/* This function feeds sensor data to the serial port. This report is visible by going to Tools->Serial Monitor, while the
 * Arduino is hooked up and running. */
void report() {
  Serial.print("DistanceLeft: \t"); Serial.print(checkDistanceLeft()); Serial.println("\t");
  Serial.print("DistanceRight: \t");Serial.print(checkDistanceRight()); Serial.print("\t");
}



/////////////////////////////////////////// ARDUINO STARTUP FUNCTION ////////////////////////////////////////////

/* This function will be ran by the Arduino once at startup. */
void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}


////////////////////////////////////////// ARDUINO CONTINUOUS FUNCTION //////////////////////////////////////////

/* This function will be run continiuously by the Arduino after it has run the setup() function. */
void loop() {
  report();
}
