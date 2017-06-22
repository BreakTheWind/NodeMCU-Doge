/*********************************************************************
This is an example sketch for our Monochrome Nokia 5110 LCD Displays

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/338

These displays use SPI to communicate, 4 or 5 pins are required to
interface

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(D2, D3, D4, D5, D6);

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
// Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!

/******************************************************************
ESP8266 with PCD8544 display

== Parts ==

* Adafruit Huzzah ESP8266 https://www.adafruit.com/products/2471

* Adafruit PCD8544/5110 display https://www.adafruit.com/product/338

* Adafruit USB to TTL serial cable https://www.adafruit.com/products/954

== Connection ==

USB TTL     Huzzah      Nokia 5110  Description
            ESP8266     PCD8544

            GND         GND         Ground
            3V          VCC         3.3V from Huzzah to display
            14          CLK         Output from ESP SPI clock
            13          DIN         Output from ESP SPI MOSI to display data input
            12          D/C         Output from display data/command to ESP
            #5          CS          Output from ESP to chip select/enable display
            #4          RST         Output from ESP to reset display
                        LED         3.3V to turn backlight on

GND (blk)   GND                     Ground
5V  (red)   V+                      5V power from PC or charger
TX  (green) RX                      Serial data from IDE to ESP
RX  (white) TX                      Serial data to ESP from IDE
******************************************************************/

// ESP8266 Software SPI (slower updates, more flexible pin options):
// pin 14 - Serial clock out (SCLK)
// pin 13 - Serial data out (DIN)
// pin 12 - Data/Command select (D/C)
// pin 5 - LCD chip select (CS)
// pin 4 - LCD reset (RST)
//Adafruit_PCD8544 display = Adafruit_PCD8544(14, 13, 12, 5, 4);

// If using an ESP8266, use this option. Comment out the other options.
// ESP8266 Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 14 on Huzzah ESP8266
// MOSI is LCD DIN - this is pin 13 on an Huzzah ESP8266
// pin 12 - Data/Command select (D/C) on an Huzzah ESP8266
// pin 5 - LCD chip select (CS)
// pin 4 - LCD reset (RST)
//Adafruit_PCD8544 display = Adafruit_PCD8544(12, 5, 4);

#define NUMFLAKES 5
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define BITMAPS 3


#define DOGE_GLCD_HEIGHT 32
#define DOGE_GLCD_WIDTH 32

const unsigned char PROGMEM doge[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x70, 0x01, 0x80, 0x00, 0x58, 0x07, 0xC0,
0x00, 0x4C, 0x1C, 0x40, 0x00, 0xC7, 0xF1, 0xC0, 0x00, 0x80, 0xE3, 0x40, 0x01, 0x80, 0x0A, 0xC0,
0x03, 0x00, 0x0C, 0x40, 0x06, 0x00, 0x0D, 0x40, 0x0C, 0x00, 0x02, 0x40, 0x18, 0x80, 0x00, 0x60,
0x19, 0x43, 0x00, 0xA0, 0x10, 0xC5, 0x80, 0x30, 0x11, 0x02, 0x00, 0x30, 0x33, 0x80, 0x00, 0xB0,
0x66, 0xC0, 0x00, 0x90, 0x63, 0x88, 0x00, 0x90, 0x61, 0x00, 0x01, 0x98, 0x61, 0x00, 0x01, 0x18,
0x32, 0xF8, 0x00, 0x08, 0x12, 0x00, 0x00, 0x0C, 0x19, 0xE0, 0x00, 0x04, 0x0C, 0x00, 0x00, 0x06,
0x04, 0x00, 0x00, 0xC2, 0x06, 0x00, 0x00, 0x82, 0x0F, 0x00, 0x01, 0x80, 0x19, 0xC2, 0x00, 0x00,
0x10, 0xFE, 0x00, 0x00, 0x10, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#define WOW_GLCD_HEIGHT 16
#define WOW_GLCD_WIDTH 16

const unsigned char PROGMEM wow[] = {
0x89, 0x91, 0x8B, 0xD1, 0x8A, 0x51, 0x8A, 0x51, 0x8A, 0x51, 0x8A, 0x51, 0x8A, 0x51, 0xAA, 0x55,
0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xFA, 0x5F, 0xDA, 0x5B, 0xDA, 0x5B, 0xDB, 0xDB, 0x89, 0x91
};

#define ZDR_GLCD_HEIGHT 24
#define ZDR_GLCD_WIDTH 24

const unsigned char PROGMEM zdr[] = {
0x7F, 0x38, 0xFC, 0x03, 0x2C, 0x84, 0x06, 0x24, 0x84, 0x0C, 0x22, 0x84, 0x08, 0x22, 0xFC, 0x18,
0x22, 0x90, 0x30, 0x22, 0x98, 0x20, 0x24, 0x88, 0x60, 0x2C, 0x8C, 0x7F, 0x38, 0x84, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xE7, 0xBD, 0xEF, 0xB4, 0xA5, 0x09, 0x94, 0x25, 0x08, 0x94, 0x25, 0x08,
0x94, 0x25, 0x08, 0xB4, 0x25, 0x08, 0xE7, 0x3D, 0x0E, 0xB4, 0x21, 0x08, 0x94, 0x21, 0x08, 0x94,
0xA1, 0x09, 0x94, 0xA1, 0x09, 0xF7, 0xA1, 0xEF, 
};

#define SODOGE_GLCD_HEIGHT 16
#define SODOGE_GLCD_WIDTH 16

const unsigned char PROGMEM sodoge[] = {
0x1E, 0xF8, 0x10, 0x88, 0x10, 0x88, 0x1E, 0x88, 0x02, 0x88, 0x02, 0x88, 0x1E, 0xF8, 0x00, 0x00,
0xC4, 0x77, 0xEA, 0xD4, 0xAA, 0x94, 0xAA, 0x84, 0xAA, 0xB7, 0xAA, 0x94, 0xEA, 0xD4, 0xC4, 0x77
};


void setup()   {
  Serial.begin(9600);

  display.begin();
  // init done
  display.setContrast(50);
  display.clearDisplay();   // clears the screen and buffer

  // draw a bitmap icon and 'animate' movement
  display.clearDisplay();   // clears the screen and buffer
  testdrawbitmap();
}


void loop() {
  
}


void testdrawbitmap() {
  uint8_t icons[NUMFLAKES][5];
  randomSeed(666);     // whatever seed
 
  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random(display.width());
    icons[f][YPOS] = 0;
    icons[f][BITMAPS] = random(6) + 1;
    switch(icons[f][BITMAPS])
    {
      case 2 :
              icons[f][DELTAY] = random(3) + 2;
              break;
      case 3 :
              icons[f][DELTAY] = random(2) + 1;
              break;
      case 4 :
              icons[f][DELTAY] = random(2) + 1;
              break;
      case 1 :
      case 5 :
      case 6 :
      case 7 :
      case 8 :
      case 9 :
      case 10:
              icons[f][DELTAY] = random(3) + 1;
              break;
    }
    
    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);
  }

  while (1) 
  {
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) 
    {
      switch(icons[f][BITMAPS])
      {
        case 2 :
                display.drawBitmap(icons[f][XPOS], icons[f][YPOS], zdr, ZDR_GLCD_WIDTH, ZDR_GLCD_HEIGHT, BLACK);
                break;
        case 3 :
                display.drawBitmap(icons[f][XPOS], icons[f][YPOS], wow, WOW_GLCD_WIDTH, WOW_GLCD_HEIGHT, BLACK);
                break;
        case 4 :
                display.drawBitmap(icons[f][XPOS], icons[f][YPOS], sodoge, SODOGE_GLCD_WIDTH, SODOGE_GLCD_HEIGHT, BLACK);
                break;
        case 1 :
        case 5 :
        case 6 :
        case 7 :
        case 8 :
        case 9 :
        case 10:
                display.drawBitmap(icons[f][XPOS], icons[f][YPOS], doge, DOGE_GLCD_WIDTH, DOGE_GLCD_HEIGHT, BLACK);
                break;
      }
    }
    display.display();
    delay(200);
    
    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) 
    {
      switch(icons[f][BITMAPS])
      {
        case 2 :
                display.drawBitmap(icons[f][XPOS], icons[f][YPOS], zdr, ZDR_GLCD_WIDTH, ZDR_GLCD_HEIGHT, WHITE);
                break;
        case 3 :
                display.drawBitmap(icons[f][XPOS], icons[f][YPOS], wow, WOW_GLCD_WIDTH, WOW_GLCD_HEIGHT, WHITE);
                break;
        case 4 :
                display.drawBitmap(icons[f][XPOS], icons[f][YPOS], sodoge, SODOGE_GLCD_WIDTH, SODOGE_GLCD_HEIGHT, WHITE);
                break;
        case 1 :
        case 5 :
        case 6 :
        case 7 :
        case 8 :
        case 9 :
        case 10:
                display.drawBitmap(icons[f][XPOS], icons[f][YPOS], doge, DOGE_GLCD_WIDTH, DOGE_GLCD_HEIGHT, WHITE);
                break;
      }
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > display.height()) 
      {
      	icons[f][XPOS] = random(display.width());
       if(icons[f][XPOS] >= 69)
       {
        icons[f][XPOS] = 68;
       }
       
      	icons[f][YPOS] = 0;
       
        icons[f][BITMAPS] = random(6) + 1;
        switch(icons[f][BITMAPS])
        {
          case 2 :
                  icons[f][DELTAY] = random(3) + 2;
                  break;
          case 3 :
                  icons[f][DELTAY] = random(2) + 1;
                  break;
          case 4 :
                  icons[f][DELTAY] = random(2) + 1;
                  break;
          case 1 :
          case 5 :
          case 6 :
          case 7 :
          case 8 :
          case 9 :
          case 10:
                  icons[f][DELTAY] = random(3) + 1;
                  break;
        }
      }
    }
   }
}
