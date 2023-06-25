#ifndef __API_H__
#define __API_H__

#include <string.h>
#include <ArduinoJson.h>
#define TRENT "Italy/Trent"
#define HOST "api.weatherapi.com"
#define PATH "/v1/forecast.json"
#define APIKEY "0526d8ca2a784a2ca17131537222912"
#define MYSSID "Honor View 10 Lite"
#define PASS_WIFI "ciao1111q"

#define CONST_DELAY_API 1000*3 //ms


typedef struct{
    const char* date;
    const char* city;
    const char* text;
    int temp_c;
    int feelslike_c;
    int humidity;
    int pressure;
    int rain;
    int snow;
}Info;

void makeRequest_(Info* info,const char* city=TRENT);

void wifiConnection_( const char* ssid=MYSSID, const char* pass_wifi=PASS_WIFI);


#endif 
