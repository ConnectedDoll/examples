#include <Wire.h>
#include "PWMServoDriver.h"

PWMServoDriver::PWMServoDriver(){

}

PWMServoDriver::~PWMServoDriver(){

}

void PWMServoDriver::begin(const uint8_t addr,const int sda,const int scl){
  wire = &Wire;
  wire->begin(sda, scl);

  pwm = new Adafruit_PWMServoDriver(addr, *wire);
  pwm->begin();
  pwm->setPWMFreq(SERVO_FREQ);
  delay(10);
}

void PWMServoDriver::setServoAngle(uint8_t pin, uint8_t angle) {
  int v = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm->writeMicroseconds(pin, v);
}
