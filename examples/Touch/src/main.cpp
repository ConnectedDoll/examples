#include <Arduino.h>
#include "connected-doll.h"

double defaultValue7 = 0;
double defaultValue8 = 0;
double defaultValue9 = 0;
double value = 0;
double thresholdValue = 0.3;

void setup() {
  Serial.begin(921600);
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, LOW);

  // 初期の数値をほぞんする
  defaultValue7 = touchRead(TOUCH7);
  defaultValue8 = touchRead(TOUCH8);
  defaultValue9 = touchRead(TOUCH9);
}

void loop() {
  // 比較する
  value = touchRead(TOUCH7)/defaultValue7;
  Serial.print("TOUCH7 value: "); Serial.println(value);
  if (value <= thresholdValue) {
    digitalWrite(LED1, HIGH);
    return;
  }

  value = touchRead(TOUCH8)/defaultValue8;
  Serial.print("TOUCH8 value:"); Serial.println(value);
  if (value <= thresholdValue) {
    digitalWrite(LED1, HIGH);
    return;
  }

  value = touchRead(TOUCH9)/defaultValue9;
  Serial.print("TOUCH9 value:"); Serial.println(value);
  if (value <= thresholdValue) {
    digitalWrite(LED1, HIGH);
    return;
  }
  
  digitalWrite(LED1, LOW);  
  delay(100);
}
