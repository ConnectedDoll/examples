#include <Arduino.h>
#include <WiFi.h>
#include "connected-doll.h"
 
// 自分の環境の WiFi接続情報に書き換える
#define WiFI_SSID "Pixel_7159"
#define WiFI_PASSWORD "649cdf5db55e"

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
  initWiFi();
}

void loop() {

}
