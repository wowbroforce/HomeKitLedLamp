#ifndef FIRE_EFFECT_H
#define FIRE_EFFECT_H

#include <FastLED.h>
#include "Buffer.h"

DEFINE_GRADIENT_PALETTE( heatmap_gp ) {
  0,     0,  0,  0,   //black
128,   255,  0,  0,   //red
224,   255,255,  0,   //bright yellow
255,   255,255,255 }; //full white

class FireEffect {
public:
    Buffer* buffer;
    uint8_t** firePixels;
    CRGBPalette16 palette = heatmap_gp;
    uint16_t width;
    uint16_t height;

    FireEffect(uint16_t _width, uint16_t _height);
    ~FireEffect();
    void update();
    void setFireSourceStrength(uint8_t strength);

private:
    void writeToBuffer();
};

#endif