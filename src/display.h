#ifndef DISPLAY_H
#define DISPLAY_H
// Using Adafruit SSD1351 library
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

extern Adafruit_ST7789 tft;
// Defined colors optimal for OLED screen
#define TFT_BLACK 0x0000
#define TFT_WHITE 0xffff
#define TFT_GREY 0x5AEB

// SSD1351 PINOUT for ESP32-S3
// GND | GND (0V) // Common
// VCC | 5V or 3.3V // Better to power with 5V if display PCB supports it
// DIN | MOSI // SPI data
// SCK | SCLK // SPI clock
// DC | DC // Distinguish between a command or its data
// RST | RST // Hardware reset, can connect to MCU RST pin as well
// CS | CS // Chip select, Set to -1 if for manually use with multiple displays

// Pin configuration
#define MISO_PIN -1
#define MOSI_PIN 1
#define CLK_PIN 2
#define CS_PIN 3
#define DC_PIN 4
#define RST_PIN 5
#define BACKLIGHT_PIN_D2 3  

#define DISPLAY_BRIGHTNESS_LOW 20
#define DISPLAY_BRIGHTNESS_HIGH 100

// Display dimensions
#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 280

void initializeLCD();
void displayBootMessage(const char *message);
void setBacklightBrightness(int brightness);
void turnOnDisplay(bool state);

#endif