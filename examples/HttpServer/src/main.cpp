#include <Arduino.h>
#include <WiFi.h>
#include "connected-doll.h"
 
// Wi-Fi接続情報を入力 ルーターへの接続情報
#define WiFI_SSID "Pixel_7159"
#define WiFI_PASSWORD "649cdf5db55e"

// HTTPサーバー
WiFiServer server(80);

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
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// 接続されたブラウザに html を返す
void outputIndexHtml(WiFiClient* client) {
  client->println("HTTP/1.1 200 OK");
  client->println("Content-type:text/html");
  client->println();

  client->print("Click <a href=\"/H\">here</a> to turn the LED on.<br>");
  client->print("Click <a href=\"/L\">here</a> to turn the LED off.<br>");

  client->println();
}

void setup() {
  Serial.begin(921600);

  pinMode(LED1, OUTPUT); 
  
  initWiFi();

  // HTTPサーバ開始
  server.begin();
}

void loop() {  
  // 接続があるか
  WiFiClient client = server.available();
  if (!client) return;
  Serial.println("New Client.");
  String currentLine = "";

  while (client.connected()) {
    if (client.available() == false) break;    
    char c = client.read();
    // Serial.write(c);
    if (c == '\n') {
      if (currentLine.length() == 0) {
        // 接続されたブラウザに htmlを返す
        outputIndexHtml(&client);
        break;
      } else {
        currentLine = "";
      }
    } else if (c != '\r') {
      currentLine += c;
    }

    // Serial.print(F("currentLine "));
    // Serial.println(currentLine);
    if (currentLine.endsWith("GET /H")) {
      // LED1 ON
      digitalWrite(LED1, HIGH);
    }
    else if (currentLine.endsWith("GET /L")) {
      // LED1 OFF
      digitalWrite(LED1, LOW);
    }    
  }

  client.stop();
  Serial.println("Client Disconnected.");
}
