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
  Serial.print("\t \t \t red: \t");Serial.print(RED());Serial.print("\t");
  Serial.print("green: \t");Serial.print(GREEN());Serial.print("\t");
  Serial.print("blue: \t");Serial.print(BLUE());Serial.print("\t");

  Serial.print("left: \t");Serial.print(checkLineLeft());Serial.print("\t");
  Serial.print("right: \t");Serial.print(checkLineRight());Serial.print("\t");

  Serial.print("IR left: \t");Serial.print(checkDistanceLeft());Serial.print("\t");
  Serial.print("IR right: \t");Serial.print(checkDistanceRight());Serial.println("\t");
  
  
  // CALIBRATION //
  
  calibrationL = 0;
  calibrationR = 0;



  // ROBOT COMMANDS //
  /* this block makes sure the car moves straight ahead when on the road, and turns when it encounters a corner to stay on the 
   * road if the car is off-road, it will turn in the direction opposite of the first sensor that detected it was off-road. */
  if (checkLineLeft() > 20) {
    while (checkLineLeft() > 20) {
      motorLeft(80);
      motorRight(20);
    }
  }
  else if (checkLineRight() > 20) {
    while (checkLineRight() > 20) {
      motorLeft(20);
      motorRight(80);
    }
  }
  else {
    motorLeft(80);
    motorRight(80);
  }

  while ( (checkDistanceLeft() > 625) || (checkDistanceRight() > 625) ) {
    motorLeft(0);
    motorRight(0);
  }

  /* checking colors.
   * red     -> T-junction right/straight 
   * green   -> T-junction right/left
   * blue    -> T-junction left/straigt
   * magenta -> crossroad traffic light
   * yellow  -> crossroad no traffic light
   */
   
  // ROOD //
  if (isRed) {
    Serial.print("ROOD");
    randNumber = random(2);
    if (ignoreColor == 1) {
      ignoreColor == 0;
      delay(50);
    }
    else if (randNumber == 0) {
      turnRight();
    }
    else {
      goStraight();
    }
  }

  // GROEN //
  else if (isGreen) {
    Serial.print("GROEN");
    randNumber = random(2);
    if (ignoreColor == 1) {
      ignoreColor == 0;
      delay(50);
    }
    else if (randNumber == 0) {
      turnRight();
    }
    else {
      turnLeft();
    }
  }

  // BLAUW //
  else if (isBlue) {
    Serial.print("BLAUW");
    randNumber = random(2);
    if (ignoreColor == 1) {
      ignoreColor == 0;
      delay(50);
    }
    else if (randNumber == 0) {
      turnLeft();
    }
    else {
      goStraight();
    }
  }

  // MAGENTA //
  else if (isMagenta) {
    Serial.print("MAGENTA");
    randNumber = random(3);
    if (ignoreColor == 1) {
      ignoreColor == 0;
      delay(50);
    }
    else {
      if (trafficLight() == 1) {
        stopCar();
        delay(3000);
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
  else if (isYellow) {
    Serial.print("GEEL");
    randNumber = random(3);
    if (ignoreColor == 1) {
      ignoreColor == 0;
      delay(50);
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

