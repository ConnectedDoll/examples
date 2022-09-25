#include <Arduino.h>
#include "connected-doll.h"

// 0.96 インチ i2c 128×64
// https://ja.aliexpress.com/item/32780054633.html

#include "SSD1306Wire.h"
#include "image.h"

SSD1306Wire display(0x3c, I2C_SDA, I2C_SCL);

void setup() {
  Serial.begin(921600);
  pinMode(LED1, OUTPUT);
  
  // pinMode(I2C_SCL, INPUT_PULLUP);
  // pinMode(I2C_SDA, INPUT_PULLUP);
  
  // 初期化
  display.init();  
  display.invertDisplay(); // 背景を白にする場合
  // display.normalDisplay(); // 背景を黒にする場合

  // Convert Image to XBM
  // 画像を XBM形式に変換
  // https://www.online-utility.org/image/convert/to/XBM
  display.drawXbm(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE_BITS);

  display.drawString(15, 20, "Hello!!"); // 文字列表示
  display.drawString(79, 20, "");

  display.display();
  display.clear();
}

bool toggle = false;

void loop() {
  display.drawXbm(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE_BITS);

  if (toggle) {
    display.drawString(15, 20, "");
    display.drawString(79, 20, "Hello!!");
  } 
  else {
    display.drawString(15, 20, "Hello!!");
    display.drawString(79, 20, "");
  }
  toggle = !toggle;

  display.display();
  display.clear();
  delay(500);
}
