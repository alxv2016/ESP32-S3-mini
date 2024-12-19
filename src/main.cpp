#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  Serial.begin(11520);
  Serial.println("Hello World");
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hellow world");
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}