# arduino-car-project
This directory contains two subdirectories - one for the main system, and one for testing the sensors/motors etc. 

The main directory (ArduinoCarProject) contains two files that need to be uploaded to the Arduino for it to work. The ArduinoCarProject.ino file contains the main Arduino code and a bunch of functions that allow the control of the car. The controlCar.ino file contains the controlCar() function, which is run continuously by the car when it is on, and contains instructions for what the car should do.

HOW TO UPLOAD TO ARDUINO:
1. Connect the Arduino to the computer
2. Open ArduinoCarProject.ino
3. Turn on the Arduino
4. Press upload (arrow in upper left corner)
5. Wait until uploading is done
6. Press the controlCar tab and repeat steps 4 and 5
7. Turn off the Arduino and disconnect it
8. Ready to go! Turn the Arduino on again and it will behave as defined in the code

The sensor-testing directory contains programs for testing the following sensors/accesories:
- HM-05 Bluetooth Module
- Servo Motor
- Reflection Sensor
- Color Sensor
- Infrared Sensor
