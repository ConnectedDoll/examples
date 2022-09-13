#include "RgbLED.h"

RgbLED::RgbLED() {

}

RgbLED::~RgbLED(){

}

bool RgbLED::begin() {
    FastLED.addLeds<SK6812, RGB_LED_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clear();    
    return true;
}


void RgbLED::show(CRGB rgb) {
    uint16_t i;
    for (i = 0; i < NUM_LEDS; i ++) {
        leds[i] = rgb;
    }
    FastLED.show();
}