#ifndef DISPLAY_H
#define DISPLAY_H

#include <bb_spi_lcd.h>

// Global objects
extern BB_SPI_LCD oled;

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

// SPI settings
#define SPI_FREQUENCY 20000000

// Display dimensions
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 128

void initializeOLED();
void displayBootMessage(const char *message);


#endif