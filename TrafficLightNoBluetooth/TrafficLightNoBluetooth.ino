/** Arduino Car System: traffic light NO BLUETOOTH
 *  Version 1.0 BETA
 *  Tjerk Reintsema
 */

/** This program drives a traffic light. After startup it will be green for goTime seconds, then red for stopTime seconds, and
 *  then it keeps going through this cycle.
 */
#define greenLED 4
#define redLED 2

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

int Fs = 2000;
int trafficLight = 0;
int count = 1;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);

  pinMode(greenLED,OUTPUT);
  pinMode(redLED,OUTPUT);
}

void loop() {
  //green(goTime);
  //red(stopTime);

  if (count >= 3000) {
    count = 0;
    digitalWrite(redLED,HIGH);
    digitalWrite(greenLED,LOW);
  }
  else if (count > 2000) {
    trafficLight = 1; 
    digitalWrite(redLED,HIGH);
    digitalWrite(greenLED,LOW);
  }
  else {
    trafficLight = 0;
    digitalWrite(greenLED,HIGH);
    digitalWrite(redLED,LOW);
  }
  Serial.println(count);
  count++;

}
