# WeatherStation
The WeatherStation machine is designed to display todays weather by retrieving information from a forecast API called "OpenWeather". What makes it special is that the weather is shown through a window where two rotating wheels create a picture of what the weather is going to look like by overlaping. In addition to that, a RGB LED is installed inside the machine and programmed to change color according to the time of the day, going from a deep blue for midnight to a violet blue for sunset, through different shades of light blue and yellow for the brightest hours of the day. For a more accurate forecast, at the bottom a LCD Display presents additional information, such as humidity, termperature, feels-like temperature, location and time.


### Requirements
* 2 ESP32 Wi-Fi & Bluetooth MCU
* RGB LED
* LCD Display
* 2 28BYJ-48 Stepper Motor  + ULN2003 Motor Driver
* 2 large gear wheels with weather drawings (?)
* 2 smaller gears to transmit the rotation
* a structure to hold everything toghether

###### Stepper Motors
To control the stepper motors we used an Arduino built-in library called "Stepper.h", that provides easy funztions to move the motor by a defined number of steps.  The 28BYJ-48 Stepper Motor has a stride angle of 5.625°, so it needs 682 steps to rotate of 120°. But in our case, the motion isn't directly transmitted to the main wheel, but through a smaller gear. This means that to get a rotation of 120° it is necessary to use the gear ratio:

![image](https://user-images.githubusercontent.com/109226936/222115208-6f9ccdab-a592-4255-a260-2a807e2f0854.png)
To interface ESP32 with the stepper motor, we use the ULN2003 motor driver that presents a connector to attach the motor, four input pins that are connected to 4 General Purpose I/O pins of the board, and two power supply pins connected to the Vin and GND pins of the ESP32. This needs to be done for each stepper motor.

###### LCD Display

###### RGB LED WS2812
All the configuration of the led can be found in the folder src in a custom library called "ledcrl.h". There, we defined a function to setup the led and one to choose the right color according with the daytime. We realized that function by defining a matrix with a predefined number of (r,g,b) values, based on the time (both hours and minutes are required), the right color is selected and displayed by the led. 
It is possbile to change the pin configuration chosen by default, but it is important to connect one pin with the ground, one with Vin and one with a MOSI pin (deafult 12)

##### Software Requirements
#### How to start
### Other Material
### Acknoledgment
### Copyright
