#include <String.h>
#include <TFT_eSPI.h> // Graphics and font library for ILI9341
#include <SPI.h>
#include <Arduino.h>
#include "display_test.h"

#define DELAY 1000 * 20 // 20s

const char* TEXT="Hello World!";

TFT_eSPI tft = TFT_eSPI();

void setup()
{
    // screen initialization
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_WHITE);
}

void loop()
{
    tft.setTextDatum(MC_DATUM);
    tft.fillScreen(TFT_WHITE);
    tft.setTextSize(2);
    tft.setTextColor(TFT_RED);
    tft.setCursor(160, 60, 2);
    tft.println(TEXT);
    tft.setTextSize(1);
    tft.setTextColor(TFT_PURPLE);
    tft.setCursor(160, 120, 2);
    tft.println("From now on some fonts will be illustrated");
    delay(5000);

    // Set text colour to orange with black background
    tft.setTextColor(TFT_ORANGE, TFT_BLACK);

    tft.fillScreen(TFT_BLACK);             // Clear screen
    tft.setFreeFont(FF18);                 // Select the font
    tft.drawString(sFF1, 160, 60, GFXFF);  // Print the string name of the font
    tft.setFreeFont(FF1);                  // Select the font
    tft.drawString(TEXT, 160, 120, GFXFF); // Print the string name of the font
    delay(1000);
    // tft.fillScreen(TFT_BLACK);
    tft.setFreeFont(FF18);                // Select the font
    tft.drawString(sFF2, 160, 60, GFXFF); // Print the string name of the font
    tft.setFreeFont(FF2);
    tft.drawString(TEXT, 160, 120, GFXFF);
    delay(1000);
    // tft.fillScreen(TFT_BLACK);
    tft.setFreeFont(FF18);                // Select the font
    tft.drawString(sFF3, 160, 60, GFXFF); // Print the string name of the font
    tft.setFreeFont(FF3);
    tft.drawString(TEXT, 160, 120, GFXFF);
    delay(1000);
    // tft.fillScreen(TFT_BLACK);
    tft.setFreeFont(FF18);                // Select the font
    tft.drawString(sFF4, 160, 60, GFXFF); // Print the string name of the font
    tft.setFreeFont(FF4);
    tft.drawString(TEXT, 160, 120, GFXFF);
    delay(1000);

    tft.fillScreen(TFT_BLACK);
    tft.setFreeFont(FF18);                // Select the font
    tft.drawString(sFF5, 160, 60, GFXFF); // Print the string name of the font
    tft.setFreeFont(FF5);
    tft.drawString(TEXT, 160, 120, GFXFF);
    delay(1000);
    // tft.fillScreen(TFT_BLACK);
    tft.setFreeFont(FF18);                // Select the font
    tft.drawString(sFF6, 160, 60, GFXFF); // Print the string name of the font
    tft.setFreeFont(FF6);
    tft.drawString(TEXT, 160, 120, GFXFF);
    delay(1000);
    // tft.fillScreen(TFT_BLACK);
    tft.setFreeFont(FF18);                // Select the font
    tft.drawString(sFF7, 160, 60, GFXFF); // Print the string name of the font
    tft.setFreeFont(FF7);
    tft.drawString(TEXT, 160, 120, GFXFF);
    delay(1000);
    // tft.fillScreen(TFT_BLACK);
    tft.setFreeFont(FF18);                // Select the font
    tft.drawString(sFF8, 160, 60, GFXFF); // Print the string name of the font
    tft.setFreeFont(FF8);
    tft.drawString(TEXT, 160, 120, GFXFF);
    delay(1000);

    // tft.fillScreen(TFT_BLACK);
    tft.setFreeFont(FF18);                 // Select the font
    tft.drawString(sFF11, 160, 60, GFXFF); // Print the string name of the font
    tft.setFreeFont(FF11);
    tft.drawString(TEXT, 160, 120, GFXFF);
    delay(1000);
    tft.fillScreen(TFT_PURPLE);
    tft.setFreeFont(FF18);                 // Select the font
    tft.drawString(sFF14, 160, 60, GFXFF); // Print the string name of the font
    tft.setFreeFont(FF14);
    tft.drawString(TEXT, 160, 120, GFXFF);
    delay(1000);
    // tft.fillScreen(TFT_BLACK);
    tft.setFreeFont(FF18);                 // Select the font
    tft.drawString(sFF15, 160, 60, GFXFF); // Print the string name of the font
    tft.setFreeFont(FF15);
    tft.drawString(TEXT, 160, 120, GFXFF);
    delay(1000);
    // tft.fillScreen(TFT_BLACK);
    tft.setFreeFont(FF18);                 // Select the font
    tft.drawString(sFF16, 160, 60, GFXFF); // Print the string name of the font
    tft.setFreeFont(FF16);
    tft.drawString(TEXT, 160, 120, GFXFF);
    delay(1000);

    tft.fillScreen(TFT_BLACK);
    tft.setFreeFont(FF18);                 // Select the font
    tft.drawString(sFF17, 160, 60, GFXFF); // Print the string name of the font
    tft.setFreeFont(FF17);
    tft.drawString(TEXT, 160, 120, GFXFF);
    delay(1000);
    // tft.fillScreen(TFT_BLACK);
    tft.setFreeFont(FF18);                 // Select the font
    tft.drawString(sFF18, 160, 60, GFXFF); // Print the string name of the font
    tft.setFreeFont(FF18);
    tft.drawString(TEXT, 160, 120, GFXFF);
    delay(1000);
    tft.fillScreen(TFT_YELLOW);
    tft.setFreeFont(FF18);                 // Select the font
    tft.drawString(sFF19, 160, 60, GFXFF); // Print the string name of the font
    tft.setFreeFont(FF19);
    tft.drawString(TEXT, 160, 120, GFXFF);
    delay(1000);
    // tft.fillScreen(TFT_BLACK);
    tft.setFreeFont(FF18);                 // Select the font
    tft.drawString(sFF20, 160, 60, GFXFF); // Print the string name of the font
    tft.setFreeFont(FF20);
    tft.drawString(TEXT, 160, 120, GFXFF);
    delay(1000);

    tft.fillScreen(TFT_BLUE);
    tft.setFreeFont(FF18);                 // Select the font
    tft.drawString(sFF21, 160, 60, GFXFF); // Print the string name of the font
    tft.setFreeFont(FF21);
    tft.drawString(TEXT, 160, 120, GFXFF);
    delay(1000);
    tft.fillScreen(TFT_RED);
    tft.setFreeFont(FF18);                 // Select the font
    tft.drawString(sFF22, 160, 60, GFXFF); // Print the string name of the font
    tft.setFreeFont(FF22);
    tft.drawString(TEXT, 160, 120, GFXFF);
    delay(1000);
}