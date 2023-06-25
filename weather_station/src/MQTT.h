#ifndef __MQTT_H__
#define __MQTT_H__

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define TOPIC_WEATHER "IoT_Meteo"
#define SERVER "broker.hivemq.com"
#define CLIENT "esp32-WeatherApi"
#define MYSSID "Honor View 10 Lite"
#define PASS_WIFI "ciao1111q"
#define CONST_DELAY_API 1000*3 //ms

void callback(char *topic, byte *payload, unsigned int length);
void setCity(char* string);
void MQTT_inizialization();
void MQTT_loop();
void lowerCaseString(char* string);
void wifiConnection_( const char* ssid=MYSSID, const char* pass_wifi=PASS_WIFI);
void parseTimeAndWeather(char* string, char* hour, char* minutes);
boolean reconnect();

#endif