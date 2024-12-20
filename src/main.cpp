#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "display.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Hello World!");
  initializeOLED();
  displayBootMessage("Hello World!");
  // No need to initialize the RGB LED
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("Testing from s3");
}
