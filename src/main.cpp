#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Hello World!");
  // No need to initialize the RGB LED
}

// the loop function runs over and over again forever
void loop() {}
