/** Arduino Car System: infrared sensor testing
 */

//////////////////////////////////////////////// INITIALIZATION /////////////////////////////////////////////////

int sample;
#define leftIRsensor A2
#define rightIRsensor A3



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



/* These functions return the distance measured by either of the IR sensors on the front of the car. 
 * This is a value between 3 and 40 cm - it doesn't work properly outside of this range */
//int checkDistanceLeft() {return (12000.0 / sampleVoltage(leftIRsensor) - 3.5);}
//int checkDistanceRight() {return (12000.0 / sampleVoltage(rightIRsensor) - 3.5);}
int checkDistanceLeft() {return sampleVoltage(leftIRsensor);}
int checkDistanceRight() {return sampleVoltage(rightIRsensor);}


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
