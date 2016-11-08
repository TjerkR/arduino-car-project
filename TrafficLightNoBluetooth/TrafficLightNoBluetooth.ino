/** Arduino Car System: traffic light NO BLUETOOTH
 *  Version 1.0 BETA
 *  Tjerk Reintsema
 */

/** This program drives a traffic light. After startup it will be green for goTime seconds, then red for stopTime seconds, and
 *  then it keeps going through this cycle.
 */
#define greenLED 3
#define redLED 4

void green(int duration) {
  digitalWrite(greenLED,HIGH);
  digitalWrite(redLED,LOW);
  delay(duration * 1000);
}

void red(int duration) {
  digitalWrite(redLED,HIGH);
  digitalWrite(greenLED,LOW);
  delay(duration * 1000);
}

const int stopTime = 5;
const int goTime = 10;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);

  pinMode(greenLED,OUTPUT);
  pinMode(redLED,OUTPUT);
}

void loop() {
  green(goTime);
  red(stopTime);

}
