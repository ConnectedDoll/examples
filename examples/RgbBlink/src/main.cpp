#include <Arduino.h>

#include "connected-doll.h"
#include "RgbLED.h"

RgbLED rgbLED;

void setup() {
  Serial.begin(921600);
  pinMode(LED1, OUTPUT);

  rgbLED.begin();
}

void loop() {
  digitalWrite(LED1, HIGH);
  delay(300);

  rgbLED.show(CRGB(0, 0, 0));
  delay(300);  
  rgbLED.show(CRGB(255, 0, 0));
  delay(300);
  rgbLED.show(CRGB(0, 255, 0));
  delay(300);
  rgbLED.show(CRGB(0, 0, 255));
  delay(300);
  rgbLED.show(CRGB(255, 255, 255));
  delay(300);

  digitalWrite(LED1, LOW);
  delay(300);
}
