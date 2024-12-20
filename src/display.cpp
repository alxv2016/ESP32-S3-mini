#include "display.h"

// BB_SPI_LCD oled;
Adafruit_SSD1351 oled = Adafruit_SSD1351(DISPLAY_WIDTH, DISPLAY_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, CLK_PIN, RST_PIN);
// Color definitions
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

void initializeOLED() {
  // Initialize OLED display with error checking
  // if (!oled.begin(LCD_SSD1351, FLAGS_NONE, SPI_FREQUENCY, CS_PIN, DC_PIN, RST_PIN,
  //                 -1, -1, MOSI_PIN, CLK_PIN)) {
  //   Serial.println("Error: OLED initialization failed.");
  //   return;
  // }

  // oled.begin(LCD_SSD1351, FLAGS_NONE, SPI_FREQUENCY, CS_PIN, DC_PIN, RST_PIN,
  //            -1, -1, MOSI_PIN, CLK_PIN);
  oled.begin();
  oled.fillScreen(BLACK);
  oled.setRotation(0);
  // oled.setSPISpeed(SPI_FREQUENCY);
  oled.setTextColor(WHITE);

  // oled.setRotation(LCD_ORIENTATION_90);
  // oled.allocBuffer();
  // oled.fillScreen(TFT_BLACK);
  // oled.setFont(FONT_8x8);
  // oled.setTextColor(TFT_WHITE);
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