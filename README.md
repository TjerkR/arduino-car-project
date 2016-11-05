# arduino-car-project
Arduino car system.

This directory contains two subdirectories - one for the main system, and one for testing the sensors/motors etc. 

The main directory (ArduinoCarProject) contains two files that need to be uploaded to the Arduino for it to work. The ArduinoCarProject.ino file contains the main Arduino code and a bunch of functions that allow the control of the car. The controlCar.ino contains the controlCar() function, which is run continuously by the car when it is on, and contains instructions for what the car should do.

The sensor-testing directory contains programs for testing the following sensors/accesories:
- HM-05 Bluetooth Module
- Servo Motor
- Reflection Sensor
- Color Sensor
- Infrared Sensor
