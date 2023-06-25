
#include <FastLED.h>
#include <Arduino.h>
 
#define NUM_LEDS 1
#define DATA_PIN 23
 
// led array
CRGB leds[NUM_LEDS];
 
void setup() {
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
}
 
void loop() {
  leds[0] = CRGB::HotPink;
  FastLED.show();
  delay(2000);

  leds[0] = CRGB::SeaGreen;
  FastLED.show();
  delay(2000);

  leds[0] = CRGB::PaleGreen;  
  FastLED.show();
  delay(2000);
}
