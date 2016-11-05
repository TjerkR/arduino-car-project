/** Arduino Car System: color sensor testing
 */

//////////////////////////////////////////////// INITIALIZATION /////////////////////////////////////////////////

#include <Wire.h>
#include "Adafruit_TCS34725.h"
/* Initialise with default values (int time = 2.4ms, gain = 1x) */
Adafruit_TCS34725 tcs = Adafruit_TCS34725();
/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

#define SCL A5
#define SDA A4


//////////////////////////////////////////// FUNCTION DEFINITIONS //////////////////////////////////////////////

/* Color sensor functions. */
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



/////////////////////////////////////////// ARDUINO STARTUP FUNCTION ////////////////////////////////////////////

/* This function will be ran by the Arduino once at startup. */
void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  tcs.begin();
}




////////////////////////////////////////// ARDUINO CONTINUOUS FUNCTION //////////////////////////////////////////

/* This function will be run continiuously by the Arduino after it has run the setup() function. */
void loop() {
  /* checking colors. */
  if (RED() > 55) {
    Serial.print("ROOD");
  }
  else if ((RED() < 35) && (GREEN() > 40) && (BLUE() < 27)) {
    Serial.print("GROEN");
  }
  else if ((RED() < 30) && (GREEN() < 37) && (BLUE() > 35)) {
    Serial.print("BLAUW");
  }
  else if ((RED() > 40) && (GREEN() < 28)) {
    Serial.print("MAGENTA");
  }
  else if ((RED() > 30) && (GREEN() > 40) && (BLUE() < 22)) {
    Serial.print("GEEL");
  }

  Serial.print("\t \t \t red: \t");Serial.print(RED());Serial.print("\t");
  Serial.print("green: \t");Serial.print(GREEN());Serial.print("\t");
  Serial.print("blue: \t");Serial.println(BLUE());
}
