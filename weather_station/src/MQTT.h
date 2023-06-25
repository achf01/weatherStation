#ifndef __MQTT_H__
#define __MQTT_H__

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define TOPIC_WEATHER "IoT_Meteo"
#define SERVER "broker.hivemq.com"
#define CLIENT "esp32-WeatherApi"

void callback(char *topic, byte *payload, unsigned int length);
void setCity(char* string);
void MQTT_inizialization();
void MQTT_publish(const char* topic, const char* payload);
void MQTT_loop();
void setReqBool(boolean req);
void lowerCaseString(char* string);
void parseTimeAndWeather(char* string, char* hour, char* minutes);
boolean reconnect();

#endif