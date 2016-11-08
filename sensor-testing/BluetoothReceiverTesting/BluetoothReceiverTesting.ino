#include <SoftwareSerial.h>

#define receiverPin 0
#define transmitterPin 1

SoftwareSerial bluetooth(receiverPin, transmitterPin);

void writeAck()
{
  uint8_t payload[] = "ACK|0|\n";
  bluetooth.write(payload, sizeof(payload));
}

void setup() {
  bluetooth.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if (bluetooth.available()) {
    String serialData = bluetooth.readString();
    Serial.println(serialData);
    writeAck();
  }
}
