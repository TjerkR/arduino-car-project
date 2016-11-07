#include <SoftwareSerial.h>

#define receiverPin 0
#define transmitterPin 1

SoftwareSerial bluetoothSerial = SoftwareSerial(receiverPin,transmitterPin);

void setup() {
  bluetoothSerial.begin(9600);
}

void loop() {
  char c = Serial.read();

}
