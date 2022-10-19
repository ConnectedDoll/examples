#include <Arduino.h>
#include "connected-doll.h"
 
void setup() {
  Serial.begin(921600);
  pinMode(LED1, OUTPUT);

  Serial.printf("Internal Total heap %d, internal Free Heap %d\n", ESP.getHeapSize(), ESP.getFreeHeap());
  Serial.printf("SPIRam Total heap %d, SPIRam Free Heap %d\n", ESP.getPsramSize(), ESP.getFreePsram());
  Serial.printf("Flash Size %d MB, Flash Speed %d\n", ESP.getFlashChipSize()/(1024*1024), ESP.getFlashChipSpeed());
  Serial.printf("ChipRevision %d, Cpu Freq %d, SDK Version %s\n", ESP.getChipRevision(), ESP.getCpuFreqMHz(), ESP.getSdkVersion());  
}

void loop() {
  digitalWrite(LED1, LOW);
  // Serial.print("LED1 "); Serial.println("LOW");
  delay(1000);
  digitalWrite(LED1, HIGH);
  // Serial.print("LED1 "); Serial.println("HIGH");
  delay(1000);
}
