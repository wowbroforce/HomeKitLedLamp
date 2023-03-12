#ifndef RENDERER_H
#define RENDERER_H

#include <FastLED.h>
#include "Buffer.h"

// LED
#define BRIGHTNESS 40           // default brightness (0-255)
#define CURRENT_LIMIT 2000      // limit how much current in milliamps the LED matrix will pull from the power supply. Bigger value -> brigher light and more heat from leds and PSU. 0 - no limit, but you should check if your PSU can handle it.
#define LED_PIN D4              // LED pin
#define COLOR_ORDER GRB         // the order of color components on the leds.

class Renderer {
public:
    bool isRendered;

    Buffer* buffer;

    void setup(Buffer* _buffer);
    void update();
    void bufferDidChanged();
};

#endif