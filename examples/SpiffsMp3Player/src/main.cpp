#include <Arduino.h>
#include "connected-doll.h"

#include <WiFi.h>
#include "Audio.h"

Audio audio;
#define GAIN 1.0f
#define FILE1 "/sound1.mp3"
#define FILE2 "/sound2.mp3"
#define FILE3 "/sound3.mp3"

double defaultValue7 = 0;
double defaultValue8 = 0;
double defaultValue9 = 0;
double value = 0;
double thresholdValue = 0.3;

void setup() {
  Serial.begin(921600);

  pinMode(LED1, OUTPUT);

  // オーディオ初期化
  audioLogger = &Serial;
  audio.begin(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setGain(GAIN);
  bool result = audio.playFile(FILE1);

  // 初期のタッチセンサ数値を保存する
  defaultValue7 = touchRead(TOUCH7);
  defaultValue8 = touchRead(TOUCH8);
  defaultValue9 = touchRead(TOUCH9);
}

void loop() {
  audio.loop();

  value = touchRead(TOUCH7)/defaultValue7;
  // Serial.print("TOUCH7 value: "); Serial.println(value);
  if (value <= thresholdValue) {
    digitalWrite(LED1, HIGH);
    // SPIFFSのMP3再生する
    if(audio.isRunning() == false){
      audio.stop();
      bool result = audio.playFile(FILE1);
    }
    return;
  }

  value = touchRead(TOUCH8)/defaultValue8;
  // Serial.print("TOUCH8 value:"); Serial.println(value);
  if (value <= thresholdValue) {
    digitalWrite(LED1, HIGH);
    // SPIFFSのMP3再生する
    if(audio.isRunning() == false){
      audio.stop();
      bool result = audio.playFile(FILE2);
    }  
    return;
  }

  value = touchRead(TOUCH9)/defaultValue9;
  // Serial.print("TOUCH9 value:"); Serial.println(value);
  if (value <= thresholdValue) {
    digitalWrite(LED1, HIGH);
    // SPIFFSのMP3再生する
    if(audio.isRunning() == false){
      audio.stop();
      bool result = audio.playFile(FILE3);
    }  
    return;
  }

  digitalWrite(LED1, LOW);
}
