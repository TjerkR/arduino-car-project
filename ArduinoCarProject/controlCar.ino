/** Arduino Car System: control function
 * Version 3.1 BETA
 * Tjerk Reintsema
 */

/** CURRENT FUNCTIONALITY OF THE CAR:
 *  - Follow a white/colored road bounded by black/gray
 *  - Back up when encountering an obstacle
 *    - Straight when both IR sensors see obstacle
 *    - Left when left IR sensor sees obstacle
 *    - Right when right IR sensor sees obstacle
 *  - Detect colors on the ground (red,green,blue,magenta,yellow)
 *  - Handle crossroads with traffic lights (magenta)
 *  - Handle crossroads without traffic lights (yellow)
 *  - Handle T-junctions (red,green,blue)
 */


/* This function tells the car what to do, using the functions defined in the main file. Make sure the controlCar() function is
 * inside the loop() function of the main file, otherwise it won't be executed. */
void controlCar() {


  if ( (checkDistanceLeft() > 625) || (checkDistanceRight() > 625) ) {
    while ( (checkDistanceLeft() > 625) || (checkDistanceRight() > 625) ) {
      motorLeft(0);
      motorRight(0);
    }
  delay(3000);
  }

  // ROBOT COMMANDS //
  /* this block makes sure the car moves straight ahead when on the road, and turns when it encounters a corner to stay on the 
   * road if the car is off-road, it will turn in the direction opposite of the first sensor that detected it was off-road. */
  if (checkLineLeft() > 95) {
    motorLeft(80);
    motorRight(20);
    while (checkLineLeft() > 95) {  
    }
  }
  else if (checkLineRight() > 95) {
    motorLeft(3);
    motorRight(100);
    while (checkLineRight() > 95) {  
    }
  }
  else {
    motorLeft(80);
    motorRight(80);
  }

  /* checking colors.
   * red     -> T-junction right/straight 
   * green   -> T-junction right/left
   * blue    -> T-junction left/straigt
   * magenta -> crossroad traffic light
   * yellow  -> crossroad no traffic light
   */
   
  // ROOD //
  if ((RED() > 43)) {
    while ((RED() > 43)) {}
    Serial.print("ROOD");
    Serial.print("\t red: \t");Serial.print(RED());Serial.print("\t");
    Serial.print("green: \t");Serial.print(GREEN());Serial.print("\t");
    Serial.print("blue: \t");Serial.print(BLUE());Serial.println("\t");
    randNumber = random(2);
    if (ignoreColor == 1) {
      ignoreColor = 0;
      delay(500);
    }
    else if (randNumber == 0) {
      turnRight();
    }
    else {
      goStraight();
    }
  }

  // GROEN //
  else if ((RED() < 35) && (GREEN() > 40) && (BLUE() < 27)) {
    while ((RED() < 35) && (GREEN() > 40) && (BLUE() < 27)) {}
    Serial.print("GROEN");
    Serial.print("\t red: \t");Serial.print(RED());Serial.print("\t");
    Serial.print("green: \t");Serial.print(GREEN());Serial.print("\t");
    Serial.print("blue: \t");Serial.print(BLUE());Serial.println("\t");
    randNumber = random(2);
    if (ignoreColor == 1) {
      ignoreColor = 0;
      delay(500);
    }
    else if (randNumber == 0) {
      turnRight();
    }
    else {
      turnLeft();
    }
  }

  // BLAUW //
  else if ((RED() < 35) && (GREEN() < 37) && (BLUE() > 34)) {
    while ((RED() < 35) && (GREEN() < 37) && (BLUE() > 34)) {}
    Serial.print("BLAUW");
    Serial.print("\t red: \t");Serial.print(RED());Serial.print("\t");
    Serial.print("green: \t");Serial.print(GREEN());Serial.print("\t");
    Serial.print("blue: \t");Serial.print(BLUE());Serial.println("\t");
    randNumber = random(2);
    if (ignoreColor == 0) {
      ignoreColor = 0;
      delay(500);
    }
    else if (randNumber == 0) {
      turnLeft();
    }
    else {
      goStraight();
    }
  }

  // MAGENTA //
  else if ((RED() > 35) && (GREEN() < 30) && (BLUE() < 35)) {
    while ((RED() > 35) && (GREEN() < 30) && (BLUE() < 35)) {}
    Serial.print("MAGENTA");
    Serial.print("\t red: \t");Serial.print(RED());Serial.print("\t");
    Serial.print("green: \t");Serial.print(GREEN());Serial.print("\t");
    Serial.print("blue: \t");Serial.print(BLUE());Serial.println("\t");
    randNumber = random(3);
    if (ignoreColor == 1) {
      ignoreColor = 0;
      delay(500);
    }
    else {
      if (trafficLight == 1) {
        waitCount = multiplier - (count - 2*multiplier);
        stopCar();
        int waitTime = map(waitTime,0,multiplier,0,8000);
        delay(waitTime);
      }
      
      if (randNumber == 0) {
        turnLeft();
      }
      else if (randNumber == 1) {
        turnRight();
      }
     else {
       goStraight();
      }
    }
  }

  // GEEL //
  else if ((RED() > 35) && (GREEN() > 35) && (BLUE() < 25)) {
    while ((RED() > 35) && (GREEN() > 35) && (BLUE() < 25)) {}
    Serial.print("GEEL");
    Serial.print("\t red: \t");Serial.print(RED());Serial.print("\t");
    Serial.print("green: \t");Serial.print(GREEN());Serial.print("\t");
    Serial.print("blue: \t");Serial.print(BLUE());Serial.println("\t");
    randNumber = random(3);
    if (ignoreColor == 1) {
      ignoreColor = 0;
      delay(500);
    }
    else if (randNumber == 0) {
      turnLeft();
    }
    else if (randNumber == 1) {
      turnRight();
    }
    else {
      goStraight();
    }
  }

  
}

