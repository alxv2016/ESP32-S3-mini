#include "display.h"

Adafruit_SSD1351 oled = Adafruit_SSD1351(DISPLAY_WIDTH, DISPLAY_HEIGHT, &SPI, CS_PIN, DC_PIN, RST_PIN);

void initializeOLED() {
  SPI.begin(SCLK_PIN, -1, MOSI_PIN, CS_PIN);
  oled.begin();

  oled.fillScreen(TFT_BLACK);
  oled.setTextColor(TFT_WHITE);
}

void displayBootMessage(const char *message) {
  int16_t x1, y1;
  uint16_t textWidth, textHeight;

  oled.getTextBounds(message, 0, 0, &x1, &y1, &textWidth, &textHeight);

  int16_t centeredX = (DISPLAY_WIDTH - textWidth) / 2;
  int16_t centeredY = (DISPLAY_HEIGHT - textHeight) / 2;

  oled.setCursor(centeredX, centeredY);
  oled.println(message);
}