#include <Arduino.h>
#include "display.h"
#include "animate.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing display and GIF decorder");
  initializeOLED();
  displayBootMessage("ALXV");
  delay(2000);
  initializeGIF();
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("Playing GIF");
  playRandomGIF();
}
