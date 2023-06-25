#include <FastLED.h>
#include <Arduino.h>
#include "ledcrl.h"

#define NUM_LEDS 1
#define DATA_PIN 15
#define UPDATES_PER_SECOND 1
#define D_NUM_COLOR 48 //double num colors
#define BRIGHTNESS  125

CRGB leds[NUM_LEDS];

int lister[D_NUM_COLOR/2][3]={
{14, 31, 106},
{48, 32, 111},
{72, 32, 115},
{93, 31, 118},
{112, 29, 119},
{131, 28, 120},
{149, 26, 119},
{166, 26, 117},
{183, 29, 114},
{198, 34, 109},
{211, 41, 105},
{224, 51, 99},
{235, 62, 93},
{245, 74, 86},
{253, 88, 79},
{255, 102, 71},
{255, 116, 62},
{255, 131, 53},
{255, 146, 44},
{255, 161, 33},
{255, 176, 20},
{255, 192, 5},
{255, 207, 0},
{255, 222, 0}
};


void led_setup(){
    FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
}

void control_led(int iter){
    if(iter%D_NUM_COLOR<(D_NUM_COLOR/2)){
        leds[0].setRGB(lister[iter%D_NUM_COLOR][0], lister[iter%D_NUM_COLOR][1], lister[iter%D_NUM_COLOR][2]);
    }else{
        leds[0].setRGB(lister[(D_NUM_COLOR-1)-iter%D_NUM_COLOR][0], lister[(D_NUM_COLOR-1)-iter%D_NUM_COLOR][1], lister[(D_NUM_COLOR-1)-iter%D_NUM_COLOR][2]); 
    }
    FastLED.show();
    Serial.println("led updated");
}
