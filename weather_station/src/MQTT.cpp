#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <string.h>
#include "MQTT.h"
#include "api.h"
#include "rotcontrol.h"
#include "ledcrl.h"

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.println("MQTT message received");
    if (strcmp(topic, TOPIC_WEATHER) == 0)
    {
        char string[length + 1];
        char hour[2];
        char minutes[2];
        // handle message arrived
        for (int i = 0; i < length; i++)
        {
            // converto il payload da byte a char e lo salvo su string
            string[i] = (char)payload[i];
        }
        string[length] = '\0';
        Serial.println(string);
        parseTimeAndWeather(string, hour, minutes);
        lowerCaseString(string);
        set_weather(string);
        int int_hour=atoi(hour)*2;
        int int_min=atoi(minutes);
        if(int_min<30){
            int_min=0;
        }else{
            int_min=1;
        }
        control_led(int_hour+int_min);
    }
}

boolean reconnect()
{
    if (client.connect(CLIENT))
    {
        Serial.println("connected to client");
        // ... and resubscribe
        client.subscribe(TOPIC_WEATHER);
    }
    return client.connected();
}

void MQTT_inizialization()
{
    Serial.println("MQTT inizialing");
    client.setServer(SERVER, 1883);
    client.setCallback(callback);
}

void MQTT_loop()
{
    client.loop();
    Serial.println("controllo!");
}

void lowerCaseString(char *string)
{
    for (int i = 0; i < strlen(string); i++)
        if (string[i] >= 'A' && string[i] <= 'Z')
            string[i] += 32;
    Serial.println(string);
}

void parseTimeAndWeather(char *string, char *hour, char *minutes)
{
    char temp[strlen(string)];
    int i = 0;
    while (string[i] != ':') // isolo l'ora
    {
        hour[i] = string[i];
        i++;
    }
    hour[i] = '\0';
    i++;
    int j = 0;
    while (string[i] != '.') // isolo i minuti
    {
        minutes[j] = string[i];
        i++;
        j++;
    }
    minutes[j] = '\0';
    i++;
    j = 0;
    while (string[i] != '\0') // isolo il meteo
    {
        temp[j] = string[i];
        i++;
        j++;
    }
    temp[j] = '\0';
    strcpy(string, temp);
}