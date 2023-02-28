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

```
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

#define IN5 25
#define IN6 26
#define IN7 27
#define IN8 14
```

###### LCD Display

###### RGB LED WS2812
All the configuration of the led can be found in the folder src in a custom library called "ledcrl.h". There, we defined a function to setup the led and one to choose the right color according with the daytime. We realized that function by defining a matrix with a predefined number of (r,g,b) values, based on the time (both hours and minutes are required), the right color is selected and displayed by the led. 
It is possbile to change the pin configuration chosen by default, but it is important to connect one pin with the ground, one with Vin and one with a MOSI pin (deafult 12)

##### Software Requirements
#### How to start
### Other Material
### Acknoledgment
### Copyright
