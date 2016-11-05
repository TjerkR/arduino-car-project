/** Arduino Car System: Color Sensor Testing
 */

#define LightSensor A0

/* These functions return the reflection measured by either of the bottom light sensors.
 * The output is a value between 0 and 100, where 0 is maximum reflection and 100 is no reflection. */
int checkLine() {return map(analogRead(LightSensor), 0, 1023, 0, 100);}

void setup() {
  Serial.begin(9600);
  digitalWrite(A0,HIGH);
}

void loop() {
  Serial.print("Sensor data: \t");
  Serial.println(analogRead(LightSensor));
}
