#include <Arduino.h>
#include "connected-doll.h"

#include <WiFi.h>
#include "Audio.h"

// 自分の環境の WiFi接続情報に書き換える
#define WiFI_SSID "Pixel_7159"
#define WiFI_PASSWORD "649cdf5db55e"

Audio audio;
#define GAIN 0.05f
#define URL "http://ice1.somafm.com/illstreet-128-mp3"

void initWiFi() {
  // ssidとpasswordを用いてWi-Fiに接続
  Serial.print("Connecting to ");
  Serial.println(WiFI_SSID);
  WiFi.begin(WiFI_SSID, WiFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // 取得したIPアドレスをシリアルに出力
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(921600);

  pinMode(LED1, OUTPUT);

  // WiFi 接続
  initWiFi();

  // オーディオ初期化
  audioLogger = &Serial;
  audio.begin(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setGain(GAIN);
  // URL先のMP3をダウンロードしながら再生する
  Serial.print(F("url ")); Serial.println(URL);
  bool result = audio.play(URL);
}

void loop() {
  audio.loop();
}
