#ifndef __LEDCRL_H__
#define __LEDCRL_H__

#include <FastLED.h>
#include <Arduino.h>

#define NUM_LEDS 1
#define D_NUM_COLOR 48 



void led_setup();
void control_led(int iter);

#endif
