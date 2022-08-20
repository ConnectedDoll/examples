#include <Arduino.h>
#include "connected-doll.h"
 
void setup() {
  Serial.begin(921600);
  pinMode(LED1, OUTPUT); 
}

void loop() {
  digitalWrite(LED1, LOW);
  Serial.print("LED1 "); Serial.println("LOW");
  delay(1000);
  digitalWrite(LED1, HIGH);
  Serial.print("LED1 "); Serial.println("HIGH");
  delay(1000);
}
