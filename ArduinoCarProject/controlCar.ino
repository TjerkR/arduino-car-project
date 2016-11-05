/** Arduino Car System: control function
 * Version 2.2
 * Tjerk Reintsema
 * 1-11-2016
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
  if (checkLineLeft() > 65) {
    while (checkLineLeft() > 65) {
      motorLeft(80);
      motorRight(30);
    }
  }
  else if (checkLineRight() > 65) {
    while (checkLineRight() > 65) {
      motorLeft(30);
      motorRight(80);
    }
  }
  else {
    motorLeft(80);
    motorRight(80);
  }
  
}

