/** Arduino Car System: Color Sensor Testing
 */

#define leftLightSensor A0
#define rightLightSensor A1

/* These functions return the reflection measured by either of the bottom light sensors.
 * The output is a value between 0 and 100, where 0 is maximum reflection and 100 is no reflection. */
int checkLineLeft() 
{
  return map(analogRead(leftLightSensor), 0, 1023, 0, 100);
}

int checkLineRight() 
{
  return map(analogRead(rightLightSensor), 0, 1023, 0, 100);
}

void setup() {
  Serial.begin(9600);
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
}

void loop() {
  Serial.print("Left: \t");
  Serial.print(analogRead(leftLightSensor));
  Serial.print("\t");
  Serial.print("Right: \t");
  Serial.println(analogRead(rightLightSensor));
  
}
