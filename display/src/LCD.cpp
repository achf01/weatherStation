#include "LCD.h"
#include "api.h"

uint8_t hh = conv2d(__TIME__), mm = conv2d(__TIME__ + 3), ss = conv2d(__TIME__ + 6); // Get H, M, S from compile time
double g_scale = 1.0;

char actualTime[20];

void reset_time(const char *weather)
{
    char string[6], min[2], hour[2];
    int i = 0, j = 0;
    parseTime(false, string, weather);
    while (string[i] != '\0')
    {
        if (i < 2)
        {
            hour[i] = string[i];
        }
        else if (i == 2)
        {
            hour[i] = '\0';

            hh = atoi(hour);
        }
        else
        {
            min[j] = string[i];
            j++;
        }
        i++;
    }
    min[j] = '\0';

    mm = atoi(min);
}

uint8_t set_time(uint8_t delayTime)
{
    ss++; // Advance second
    if (ss == 60)
    {                // Check for roll-over
        ss = 0;      // Reset seconds to zero
        mm++;        // Advance minute
        delayTime++; // delayTime measured in minutes
        if (mm > 59)
        { // Check for roll-over
            mm = 0;
            hh++; // Advance hour
            if (hh > 23)
            {           // Check for 24hr roll-over (could roll-over on 13)
                hh = 0; // 0 for 24 hour clock, set to 1 for 12 hour clock
            }
        }
    }
    return delayTime;
}

void buildTimeString(TFT_eSPI tft)
{
    char min[3];

    if (hh < 10)
        sprintf(actualTime, "0%d:", hh);
    else
        sprintf(actualTime, "%d:", hh);

    if (mm < 10)
        sprintf(min, "0%d", mm);
    else
        sprintf(min, "%d", mm);

    strcat(actualTime, min);
}

void drawWeather(weather_info weather, TFT_eSPI tft)
{
    Serial.println("Starting drawing weather");
    char string[MAX_CHAR];
    tft.fillScreen(TFT_WHITE);
    tft.setCursor(10, 50, 2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_BLACK);
    parseTime(true, string, weather.date);
    tft.drawString(string, 20, 30, 4);
    tft.drawString(weather.weather, 20, 110, 4);
    tft.setTextSize(2);
    tft.drawString(weather.city, 20, 70, 2);
    buildTimeString(tft);
    tft.drawString(actualTime, 180, 10, 4);
    Serial.println("Weather drew");
    tft.setTextColor(TFT_RED);
    sprintf(string, "T: %d (C)", weather.temp_c);
    tft.drawString(string, 190, 160, 2);
    tft.setTextSize(1);
    tft.setCursor(20, 140, 2);
    sprintf(string, "Feelslike temperature: %d (C)", weather.feelslike_c);
    tft.println(string);
    tft.setCursor(20, tft.getCursorY(), 2);
    tft.setTextColor(TFT_BLUE);
    sprintf(string, "Humidity percentage: %d", weather.humidity);
    tft.println(string);
    tft.setCursor(20, tft.getCursorY(), 2);
    sprintf(string, "Precipitation: 33 (mm)", weather.rain);
    tft.println(string);
    tft.setCursor(20, tft.getCursorY(), 2);
    sprintf(string, "Wind: %d (km/h)", weather.wind);
    tft.println(string);
}