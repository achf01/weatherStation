#include <Arduino.h>
#include "api.h"
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
//using namespace std;

void wifiConnection_(const char* ssid, const char* pass_wifi){
    WiFi.begin(ssid, pass_wifi);
    Serial.print("Connecting to WiFi");
    while( WiFi.status()!= WL_CONNECTED){
        Serial.print(".");
        delay(500);
    }
    // Serial.println("\nConnected to the WiFi network");
    // Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}


void makeRequest_(Info* info,const char* city){
    WiFiClient client;
    if(client.connect(HOST, 80)){
      Serial.println("Connected to server");  
    }else{
      Serial.println("Connection failed");    
    }

    //HTTP request
    if(client.connected()){
        client.println("GET " PATH "?key=" APIKEY "&q=" TRENT " HTTP/1.0");
        client.println("Host: " HOST);      
        client.println("Connection: close");
        client.println();
        Serial.println("request made");
        while(!client.available()){
      //Serial.println("Waiting for client");
    }
    while(client.available()){
        char status[32] = {0};
        client.readBytesUntil('\r', status, sizeof(status));
        if (strcmp(status, "HTTP/1.1 200 OK") != 0){
            Serial.print(F("Unexpected response: "));
            Serial.println(status);
            return;
        }

      
  // Skip HTTP headers
    char endOfHeaders[] = "\r\n\r\n";
        if (!client.find(endOfHeaders)){
            Serial.println(F("Invalid response"));
            return;
        }

      DynamicJsonDocument doc(65536);
      DeserializationError error = deserializeJson(doc, client);
      
      if(!error){
        info->date=doc["location"]["localtime"];
        info->city=doc["location"]["name"];
        info->text=doc["current"]["condition"]["text"];
        info->temp_c=doc["current"]["temp_c"];
        info->feelslike_c=doc["current"]["feelslike_c"];
        info->humidity=doc["current"]["humidity"];
        info->pressure=doc["current"]["pressure_mb"]; 
        info->rain=doc["forecast"]["forecastday"]["0"]["day"]["totalprecip_mm"];
        info->snow=doc["forecast"]["forecastday"]["0"]["day"]["totalsnow_cm"];
      }else{
        Serial.print("Error in decoding:  ");
        Serial.println(error.c_str());  
      }
      
    }
  }
}
