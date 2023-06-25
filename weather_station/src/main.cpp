#include <Arduino.h>
#include <ArduinoJson.h>
#include <string.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Stepper.h>
#include <PubSubClient.h>
#include "step.h"
#include "ledcrl.h"
#include "rotcontrol.h"
#include "MQTT.h"
using namespace std;

int iter = 0;
up state_up = STORM;
down state_down = SUN;
Stepper stp1 = init1();
Stepper stp2 = init2();
info_reduced info;

void setup()
{
  Serial.begin(9600);
  wifiConnection_();
  led_setup();
  MQTT_inizialization();
  info=init_info(&state_up, &state_down);
}

void loop()
{
  if (reconnect())
    MQTT_loop(); // control message presence
  
  delay(CONST_DELAY_API);
}

void set_weather(char *weather)
{
  info.sun = false;
  info.rain = false;
  info.storm = false;
  info.clear = false;
  info.cloud = false;
  info.snow = false;

  // Define if snow, rain or sun
  if ((strstr(weather, "snow") != NULL) || (strstr(weather, "sleet") != NULL) || strstr(weather, "freezing") != NULL)
  {
    info.snow = true;
  }

  else if ((strstr(weather, "rain") != NULL) || (strstr(weather, "drizzle") != NULL) || strstr(weather, "storm") != NULL)
  {
    info.rain = true;
  }
  else
    info.sun = true;

  // Define if clear, storm or cloud

  if ((strstr(weather, "clear") != NULL) || (strstr(weather, "plain") != NULL) || strstr(weather, "sunny") != NULL)
  {
    info.clear = true;
  }
  else if (strstr(weather, "storm") != NULL || strstr(weather, "thunder") != NULL)
  {
    info.storm = true;
  }
  else
  {
    info.cloud = true;
  }
  rot_control(&state_up, &state_down, info, &stp1, &stp2);
}