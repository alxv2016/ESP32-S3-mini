#include "display.h"

BB_SPI_LCD oled;

void initializeOLED() {
  // Initialize OLED display with error checking
  if (!oled.begin(LCD_SSD1351, FLAGS_NONE, SPI_FREQUENCY, CS_PIN, DC_PIN, RST_PIN,
                  -1, -1, MOSI_PIN, CLK_PIN)) {
    Serial.println("Error: OLED initialization failed.");
    return;
  }

  oled.begin(LCD_SSD1351, FLAGS_NONE, SPI_FREQUENCY, CS_PIN, DC_PIN, RST_PIN,
             -1, -1, MOSI_PIN, CLK_PIN);
  oled.setRotation(LCD_ORIENTATION_90);
  oled.allocBuffer();
  oled.fillScreen(TFT_BLACK);
  oled.setFont(FONT_8x8);
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