#ifndef __API_H__
#define __API_H__

#include <string.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define TRENT "Italy/Trento"
#define HOST "api.weatherapi.com"
#define PATH "/v1/forecast.json"
#define APIKEY "0526d8ca2a784a2ca17131537222912"
#define MYSSID "Usta"       //wifi name
#define PASS_WIFI "Avvoltoio"        //wifi password

#define CONST_DELAY_API 600000 * 30 // from ms -> s, 30 min

typedef struct
{
    const char *date;
    const char *city;
    const char *weather;
    const char *icon;
    int temp_c;
    int feelslike_c;
    int humidity;
    int pressure;
    int rain;
    int wind;
} weather_info;

/*
    Function that handle the HTTP request that need to be done
*/
void makeRequest_(weather_info *info, const char *city=TRENT);

/*
    Function that handle the connection to the wifi    
*/
void wifiConnection_(const char *ssid = MYSSID, const char *pass_wifi = PASS_WIFI);

/*
    separate date and time in two different string
*/
void parseTime(boolean ora_or_date, char* ora, const char* weather);

#endif
