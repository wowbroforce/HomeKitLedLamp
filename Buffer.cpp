#include "Buffer.h"

Buffer::Buffer(uint16_t _width, uint16_t _height) {
    width = _width;
    height = _height;
    numberOfLeds = width * height;
    
    leds = new CRGB[width * height];
}

Buffer::~Buffer() {
    delete[] leds;
}

void Buffer::fill(CRGB color) {
    for (uint16_t i = 0; i < width; ++i) {
        for (uint16_t j = 0; j < height; ++j) {
            leds[width + j * height] = color;
        }
    }
}

void Buffer::set(CRGB color, uint16_t x, uint16_t y) {
    leds[x + y * height] = color;
}

void Buffer::invokeBufferDidChanged() {
    // if (bufferDidChanged == NULL) return;

    // bufferDidChanged();
}
