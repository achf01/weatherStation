#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "MQTT.h"
#include "api.h"

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.println("MQTT message received");
    if (strcmp(topic, TOPIC_CITY) == 0)
    {
        char string[length + 1];
        // handle message arrived
        for (int i = 0; i < length; i++)
        {
            // convert the payload from byte to char and save it as a string
            string[i] = (char)payload[i];
        }
        string[length] = '\0';
        setCity(string);  // set city name
        setReqBool(true); // send a new request
    }
}

boolean reconnect()
{
    boolean connected = client.connect(CLIENT);
    if (connected)
    {
        Serial.println("connected to client");
        // ... and resubscribe
        client.subscribe(TOPIC_CITY);
    }
    else
        Serial.println(connected);
    return client.connected();
}

void MQTT_inizialization()
{
    Serial.println("MQTT inizialing");
    client.setServer(SERVER, 1883);
    client.setCallback(callback);
}

void MQTT_publish(const char *topic, const char *payload)
{
    client.publish(topic, payload);
}

void MQTT_loop()
{
    client.loop();
}
