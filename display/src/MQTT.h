#ifndef __MQTT_H__
#define __MQTT_H__

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define TOPIC_CITY "IoT_Luogo"
#define TOPIC_WEATHER "IoT_Meteo"
#define SERVER "broker.hivemq.com"
#define CLIENT "esp32-LCD"


/* 
    Handler for MQTT message exchange
*/
void callback(char *topic, byte *payload, unsigned int length);

/*
    Function used to set the name of the city
*/
void setCity(char* string);

/*
    Function that handles the inizialization of MQTT system
*/
void MQTT_inizialization();

/*
    Function used to publish on a MQTT topic     
*/
void MQTT_publish(const char* topic, const char* payload);

/*
    Function used to check if there has been a change in a subscribed topic
*/
void MQTT_loop();

/*
    Function used to notify if a new HTPP request has to be sent    
*/
void setReqBool(boolean req);

/*
    Function that handle the connection to the MQTT broker and the subscription to topics
*/
boolean reconnect();

#endif