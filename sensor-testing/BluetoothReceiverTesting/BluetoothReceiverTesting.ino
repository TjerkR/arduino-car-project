#include <SoftwareSerial.h>

#define receiverPin 0
#define transmitterPin 1

SoftwareSerial bluetoothSerial(receiverPin,transmitterPin);

void setup() {
  bluetoothSerial.begin(9600);
}

void loop() {
  char c = bluetoothSerial.read();

}
