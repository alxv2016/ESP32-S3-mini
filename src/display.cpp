#include "display.h"

// PWM Configuration
const int BACKLIGHT_PWM_CHANNEL = 0;
const int BACKLIGHT_PWM_FREQ = 5000;
const int BACKLIGHT_PWM_RESOLUTION = 8;
const float PERCENTAGE_TO_PWM_FACTOR = 2.55;

// Initialize the display
Adafruit_ST7789 tft = Adafruit_ST7789(CS_PIN, DC_PIN, RST_PIN);

// Function to set backlight brightness (0–100%)
void setBacklightBrightness(int brightnessPercentage) {
    brightnessPercentage = constrain(brightnessPercentage, 0, 100); // Ensure bounds
    int dutyCycle = brightnessPercentage * PERCENTAGE_TO_PWM_FACTOR; // Map to 0–255
    ledcWrite(BACKLIGHT_PWM_CHANNEL, dutyCycle);
}

void turnOnDisplay(bool state) {
    tft.enableDisplay(state);
}

// Initialize the OLED display
void initializeLCD() {
    // Setup PWM for the backlight
    ledcSetup(BACKLIGHT_PWM_CHANNEL, BACKLIGHT_PWM_FREQ, BACKLIGHT_PWM_RESOLUTION);
    ledcAttachPin(BACKLIGHT_PIN_D2, BACKLIGHT_PWM_CHANNEL);
    
    turnOnDisplay(true); // Turn on the display
    setBacklightBrightness(50); // Set to full brightness initially

    // Initialize display
    tft.init(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    Serial.println("Display initialized");
}

// Display a message on the screen
void displayBootMessage(const char *message) {
  int16_t x1, y1;
  uint16_t textWidth, textHeight;
  tft.setTextSize(1); 
  tft.getTextBounds(message, 0, 0, &x1, &y1, &textWidth, &textHeight);

  int16_t centeredX = (DISPLAY_WIDTH - textWidth) / 2;
  int16_t centeredY = (DISPLAY_HEIGHT - textHeight) / 2;

  tft.setCursor(centeredX, centeredY);
  tft.println(message);
}