#include <Arduino.h>
#include <WiFi.h>
#include "connected-doll.h"
 
// AP モードの Wi-Fi接続情報
#define WiFI_SSID "connected-doll"
#define WiFI_PASSWORD "649cdf5db55e"
const IPAddress ip(192,168,11,2); 
const IPAddress subnet(255,255,255,0); 

WiFiServer server(80);

void initWiFiAp() {
  //WiFiのアクセスポイントの設定
  WiFi.softAP(WiFI_SSID, WiFI_PASSWORD);
  //IP及びサブネットマスクの設定
  WiFi.softAPConfig(ip, ip, subnet); 
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

  initWiFiAp();

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
