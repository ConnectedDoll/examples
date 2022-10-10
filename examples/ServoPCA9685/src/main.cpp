#include <Arduino.h>
#include "connected-doll.h"
#include "PWMServoDriver.h"

PWMServoDriver pwm;
#define SERVO_DRIVER_ADDR 0x40
#define SERVO_PIN 0

int angle = 0;
int v = 1;

void setup() {
  Serial.begin(921600);
  pinMode(LED1, OUTPUT);

  pinMode(I2C_SDA, INPUT_PULLUP);
  pinMode(I2C_SCL, INPUT_PULLUP);

  // サーボドライバを初期化
  pwm.begin(SERVO_DRIVER_ADDR, I2C_SDA, I2C_SCL);
  pwm.setServoAngle(SERVO_PIN, 0);

  delay(1000);
}

void loop() {
  // サーボドライバのサーボを 角度指定で稼働させる
  angle += (10 * v);
  if (angle > 180) {
    v = -1;
    angle = 180;
  }
  if (angle < 0){
    v = 1;
    angle = 0;
  }
  pwm.setServoAngle(SERVO_PIN, angle);
  Serial.print("angle "); Serial.println(angle);

  digitalWrite(LED1, LOW);
  Serial.print("LED1 "); Serial.println("LOW");
  delay(500);
  digitalWrite(LED1, HIGH);
  Serial.print("LED1 "); Serial.println("HIGH");
  delay(500);
}
