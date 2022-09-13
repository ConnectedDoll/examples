#ifndef __RGB_LED_H_
#define __RGB_LED_H_

#include <FastLED.h>

#define RGB_LED_PIN 4
#define NUM_LEDS    4
#define BRIGHTNESS  30

class RgbLED {
public:
    RgbLED();
    ~RgbLED();
    bool begin();
    void show(CRGB rgb);
private:
    CRGB leds[4];
};

#endif // __RGB_LED_H_