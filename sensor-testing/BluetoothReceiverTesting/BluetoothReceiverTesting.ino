#include <SoftwareSerial.h>

#define receiverPin 0
#define transmitterPin 1

void setup() {
  SoftwareSerial.begin();
  SoftwareSerial(receiverPin,transmitterPin);
}

void loop() {
  char c = Serial.read();
  if ( c ==

}
