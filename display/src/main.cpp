#include "MQTT.h"
#include "LCD.h"
using namespace std;

#define CITY_MAX_LENGHT 59 // The city with the longest name in the world has 58 character

char citta[CITY_MAX_LENGHT];
TFT_eSPI tft = TFT_eSPI();
boolean sendReq = true; // To check if a new MQTT message has been received
uint8_t delayTime = 0;  // To send another request after some time without inputs
uint8_t minTime = 0;    // If a minute passed, refresh the display
weather_info weather;
boolean connected;

void setup()
{
  Serial.printf("Setup");
  strcpy(citta, "Izmir"); // by default the city is Trento
  // connection initialization
  Serial.begin(9600);
  wifiConnection_();

  // MQTT initialization
  MQTT_inizialization();

  // screen initialization
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_WHITE);
}

void loop()
{
  delayTime = set_time(delayTime);

  if (delayTime >= CONST_DELAY_API || sendReq == true)
  {
    Serial.println("Check connection");
    Serial.println(WiFi.status());
    if ((WiFi.status() == WL_CONNECTED))
    {
      makeRequest_(&weather, citta);
      reset_time(weather.date);
      drawWeather(weather, tft);
      sendReq = false;
      delayTime = 0;
    }
    connected = reconnect();
    if (!connected)
    {
      Serial.println("Not connected to client");
    }
    else
    {
      // Client connected

      char message[100];
      parseTime(false, message, weather.date);
      Serial.println("Sending MQTT message");
      strcat(message, ".");
      strcat(message, weather.weather);
      MQTT_publish(TOPIC_WEATHER, message); // Manda un messaggio con la seguente struttura: hh:mm.weather
      Serial.println("MQTT message sent");
    }
  }

  if (minTime != delayTime)
  {
    minTime = delayTime;
    drawWeather(weather, tft);
  }

  if (connected == true)
    MQTT_loop();
  else
    Serial.println("Not connected");

  delay(1000);
}

void setCity(char *string)
{
  strcpy(citta, string);
}

void setReqBool(boolean req)
{
  sendReq = req;
}

void lowerCaseString(char *string)
{
    for (int i = 0; i < strlen(string); i++)
        if (string[i] >= 'A' && string[i] <= 'Z')
            string[i] += 32;
    Serial.println(string);
}

boolean verifyCity()
{
  char temp1[strlen(citta)];
  char temp2[strlen(weather.city)];
  strcpy(temp1,citta);
  strcpy(temp2, weather.city);
  lowerCaseString(temp1);
  lowerCaseString(temp2);

  if (strcmp(temp1, temp2) != 0)
    return true;
  return false;
}