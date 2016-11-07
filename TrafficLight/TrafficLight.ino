/** Arduino Car System: traffic light
 *  Version 1.0 BETA
 *  Tjerk Reintsema
 */

/** This program drives a traffic light. It tells the light whether to be red or green, and also sends this signal to the Arduino
 *  via Bluetooth.
 */

#include <SoftwareSerial.h>

#define receiverPin 0
#define transmitterPin 1
#define greenLED 3
#define redLED 4

void green(int duration) {
  digitalWrite(greenLED,HIGH);
  digitalWrite(redLED,LOW);
  delay(duration * 1000);

  //sendSignal(0);
}

void red(int duration) {
  digitalWrite(redLED,HIGH);
  digitalWrite(greenLED,LOW);
  delay(duration * 1000);

  //sendSignal(1);
}

const int stopTime = 5;
const int goTime = 10;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  SoftwareSerial.begin();
  SoftwareSerial(receiverPin,transmitterPin);

  pinMode(greenLED,OUTPUT);
  pinMode(redLED,OUTPUT);
}

void loop() {
  green(goTime);
  red(stopTime);

}
