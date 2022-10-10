#ifndef __PWM_SERVO_DRIVER_H_
#define __PWM_SERVO_DRIVER_H_

#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN 500 
#define SERVOMAX 2500

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

class PWMServoDriver {
public:
    PWMServoDriver();
    ~PWMServoDriver();
    void begin(const uint8_t addr,const int sda,const int scl);
    void setServoAngle(uint8_t pin, uint8_t angle);
private:
    TwoWire* wire = NULL;
    Adafruit_PWMServoDriver* pwm = NULL;
};

#endif // __PWM_SERVO_DRIVER_H_