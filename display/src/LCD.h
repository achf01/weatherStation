#ifndef __LCD_H__
#define __LCD_H__

#include <TFT_eSPI.h> // Graphics and font library for ILI9341
#include <SPI.h>
#include <time.h>
#include <string.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "api.h"

#define MAX_CHAR 60

/*
    Update time
*/
uint8_t set_time(uint8_t delayTime);       

/*
    Draw on LCD display information about weather
*/
void drawWeather(weather_info weather, TFT_eSPI tft);

/*
    Create the string containing hour, minute to draw
*/
void buildTimeString(TFT_eSPI tft);

/*
    Function that set time from the data gathered by the HTTP request
*/
void reset_time(const char* weather);

boolean verifyCity();

/*
    Function to convert time from string to int
*/
static uint8_t conv2d(const char *p)
{
    uint8_t v = 0;
    if ('0' <= *p && *p <= '9')
        v = *p - '0';
    return 10 * v + *++p - '0';
}


#endif