# WeatherStation
The WeatherStation machine is designed to display todays weather by retrieving information from a forecast API called "OpenWeather". What makes it special is that the weather is shown through a window where two rotating wheels create a picture of what the weather is going to look like by overlaping. In addition to that, a RGB LED is installed inside the machine and programmed to change color according to the time of the day, going from a deep blue for midnight to a violet blue for sunset, through different shades of light blue and yellow for the brightest hours of the day. For a more accurate forecast, at the bottom a LCD Display presents additional information, such as humidity, termperature, feels-like temperature, location and time.


### Requirements
* 2 ESP32 Wi-Fi & Bluetooth MCU (DOIT-V1-DEVKIT)
* RGB LED
* ILI9341 TFT LCD Display
* 2 28BYJ-48 Stepper Motor  + ULN2003 Motor Driver
* 2 large gear wheels with weather drawings (?)
* 2 smaller gears to transmit the rotation
* a structure to hold everything toghether

###### Stepper Motors
To control the stepper motors we used an Arduino built-in library called "Stepper.h", that provides easy funztions to move the motor by a defined number of steps.  The 28BYJ-48 Stepper Motor has a stride angle of 5.625°, so it needs 682 steps to rotate of 120°. But in our case, the motion isn't directly transmitted to the main wheel, but through a smaller gear. This means that to get a rotation of 120° it is necessary to use the gear ratio:

![image](https://user-images.githubusercontent.com/109226936/222115208-6f9ccdab-a592-4255-a260-2a807e2f0854.png)

To interface ESP32 with the stepper motor, we use the ULN2003 motor driver that presents a connector to attach the motor, four input pins that are connected to 4 General Purpose I/O pins of the board, and two power supply pins connected to the Vin and GND pins of the ESP32. This needs to be done for each stepper motor.

###### LCD Display
To use the display we used an Arduino built-in library called ["TFT_eSPI.h"](https://github.com/Bodmer/TFT_eSPI), which provide functions to draw and write on the display, with the possibility to set the colors. The ILI9341 display we choose is 2.8" with a resolution of 240x320 pixels.
The display communicate with the ESP32 through SPI protocol, 5 input pins are connected to 5 General Purpose I/O pins on the board, and three power supply pins connected to the Vin, 3v3 and GND of the ESP32. 

###### RGB LED WS2812
All the configuration of the led can be found in the folder src in a custom library called "ledcrl.h". There, we defined a function to setup the led and one to choose the right color according with the daytime. We realized that function by defining a matrix with a predefined number of (r,g,b) values, based on the time (both hours and minutes are required), the right color is selected and displayed by the led. 
It is possbile to change the pin configuration chosen by default, but it is important to connect one pin with the ground, one with Vin and one with a MOSI pin (deafult 12)

###### Physical structure
In the folder svg_files you can find all the models of the structure we created for our project. To make our structure and disks we used a laser cutting machine in FabLab, which is a workshop situaded in the University of Trento that offers digital fabrication tools 

##### Software Requirements (DA CONTROLLARE)
To devolop the project we have decided to use [Platform.IO](https://platformio.org/), an extension of Visual Studio Code that has all the functionality of Arduino IDE and an easier interface, in particular for the creation of structured projects with many files. Besides this, it is possible to obtain the same result in Arduino IDE, manually manging all the project structure.
In the repository there are two different projects, one for each ESP32. This choice has been made because the LCD screen reequires many pins and memory to work properly. 
To handle information exchange between the two ESP32 and the PC, we choose to use MQTT protocol, for sending information from PC to ESP32 (and to monitor that messages are exchanging correctly) we used the [MQTTX interface](https://mqttx.app/docs/downloading-and-installation).
Since we used many external libraries, it is possible to install it thanks to the Platform.IO manager using the following commands in the platform control cli 

Weather station
```console
pio pkg install --library "fastled/FastLED@^3.5.0"
pio pkg install --library "arduino-libraries/Stepper@^1.1.3"
pio pkg install --library "bblanchon/ArduinoJson@^6.20.1" 
pio pkg install --library "knolleary/PubSubClient@^2.8"
```

Display controller
```console
pio pkg install --library "bodmer/TFT_eSPI@^2.5.2"
pio pkg install --library "knolleary/PubSubClient@^2.8"
pio pkg install --library "bblanchon/ArduinoJson@^6.20.1" 
```



### How to start
#### Weather station


#### Display controller
##### Pin setup
First to make sure that the display works set up the pins properly by:
1) Display_Controller -> .pio -> libdeps -> TFT_eSPI -> User_Setup.h
2) Uncomment (if commented) "#define ILI9341_DRIVER" and comment all the others drivers setup
3) Uncomment (if commented) and set the lines

![Immagine 2023-03-23 115922](https://user-images.githubusercontent.com/75731638/227183194-501f8798-0ddf-4aa6-aaa1-cc056f9ecbb1.png)

##### MQTT 
For receiving and sending information (respectively from PC and to the other ESP32) we decided to use a MQTT broker. In particular we decided to use [HiveMQ MQTT broker](https://www.hivemq.com/public-mqtt-broker/), however it should work even using others MQTT brokers.
Remember to set up the following macros in the "MQTT.h" file:
1) ```TOPIC_CITY``` name of the topic in the MQTT broker where you receive the city name from PC
4) ```TOPIC_HOUR``` name of the topic in the MQTT broker where you send the actual time to the other ESP32
5) ```TOPIC_WEATHER``` name of the topic in the MQTT broker where you send the actual weather to the other ESP32
6) ```SERVER``` name of the broker (can be found easily on the official site of the MQTT broker you choose) 

It's the handler of MQTT message, every time a message in the topic ```TOPIC_CITY``` is published, the ```callback``` function will save the message (containing the city name) and send a new HTPP request, asking for data about the city's weather.
![Immagine 2023-03-23 125840](https://user-images.githubusercontent.com/75731638/227197372-7ea91064-3cd2-4296-a078-53e00da6a8e6.png)

##### Weather API 

Remember to set up the following macros in the "api.h" file:
1) ```MYSSID``` WiFi name
2) ```PASS_WIFI``` WiFi password
3) ```CONST_DELAY_API``` time to pass between a request sending and another without receiving new inputs (by default 30 minutes)

### Other Material


### Acknoledgment
### Copyright
