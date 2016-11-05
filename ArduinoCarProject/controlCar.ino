/** Arduino Car System: control function
 * Version 2.3
 * Tjerk Reintsema
 * 2-11-2016
 */

/** CURRENT FUNCTIONALITY OF THE CAR:
 *  - Follow a white/colored road bounded by black/gray
 *  - Back up when encountering an obstacle
 *    - Straight when both IR sensors see obstacle
 *    - Left when left IR sensor sees obstacle
 *    - Right when right IR sensor sees obstacle
 */

/* This function tells the car what to do, using the functions defined in the main file. Make sure the controlCar() function is
 * inside the loop() function of the main file, otherwise it won't be executed. */
void controlCar() {
  
  // CALIBRATION //
  
  calibrationL = 0;
  calibrationR = -10;



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

  /* this block makes the car back up when encountering an obstacle. */
  if ( (checkDistanceLeft() < 5) && (checkDistanceRight() < 5) ) {
    beep(100);
    motorLeft(-50);
    motorRight(-50);
    delay(50);beep(100);delay(50);beep(100);
    delay(1000);
    motorLeft(0);
    motorRight(0);
  }
  else if (checkDistanceLeft() < 5) {
    beep(100);
    motorLeft(-15);
    motorRight(-50);
    delay(1250);
    motorLeft(0);
    motorRight(0);
  }
  else if (checkDistanceRight() < 5) {
    beep(100);
    motorLeft(-50);
    motorRight(-15);
    delay(1250);
    motorLeft(0);
    motorRight(0);
  }


  
}

