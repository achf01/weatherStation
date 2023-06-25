#include "api.h"
using namespace std;

void wifiConnection_(const char *ssid, const char *pass_wifi)
{
  WiFi.begin(ssid, pass_wifi);
  Serial.println("");
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnected to the WiFi network");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void makeRequest_(weather_info *info, const char *city)
{
  WiFiClient client;
  if (client.connect(HOST, 80))
  {
    Serial.println("Connected to server");
  }
  else
  {
    Serial.println("Connection failed");
  }

  // HTTP request
  if (client.connected())
  {
    char string[100]="GET ";
    strcat(string, PATH);
    strcat(string, "?key=");
    strcat(string, APIKEY);
    strcat(string, "&q=");
    strcat(string, city);
    strcat(string, " HTTP/1.0");
    client.println(string);
    client.println("Host: " HOST);
    client.println("Connection: close");
    client.println();
    Serial.println("request made");
    while (!client.available())
    {
      Serial.println("Waiting for client");
    }
    while (client.available())
    {
      char status[64] = {0};
      client.readBytesUntil('\r', status, sizeof(status));
      if (strcmp(status, "HTTP/1.0 200 OK") != 0)
      {
        Serial.print(F("Unexpected response: "));
        Serial.println(status);
        return;
      }
      // Skip HTTP headers
      char endOfHeaders[] = "\r\n\r\n";
      if (!client.find(endOfHeaders))
      {
        Serial.println(F("Invalid response"));
        return;
      }

      DynamicJsonDocument doc(32768);
      DeserializationError error = deserializeJson(doc, client);

      if (!error)
      {
        info->date = doc["location"]["localtime"];
        info->city = doc["location"]["name"];
        info->weather = doc["current"]["condition"]["text"];
        info->icon = doc["current"]["condition"]["icon"];
        info->temp_c = doc["current"]["temp_c"];
        info->feelslike_c = doc["current"]["feelslike_c"];
        info->humidity = doc["current"]["humidity"];
        info->pressure = doc["current"]["pressure_mb"];
        info->rain = doc["current"]["precip_mm"];
        info->wind = doc["current"]["wind_kph"];
      }
      else
      {
        Serial.print("Error in decoding:  ");
        Serial.println(error.c_str());
      }
    }
  }
}

void parseTime(boolean ora_or_date, char *ora, const char *weather)
{
  uint8_t i = 0;

  strcpy(ora, "");
  if (ora_or_date == true)
  {
    while (weather[i] != ' ')
    {
      ora[i] = weather[i];
      i++;
    }
    ora[i] = '\0';
  }
  else
  {
    uint8_t j = 0;
    while (weather[i] != ' ')
    {
      i++;
    }
    i++;
    while (weather[i] != '\0')
    {
      ora[j] = weather[i];
      i++;
      j++;
    }
    ora[j] = '\0';
  }
}