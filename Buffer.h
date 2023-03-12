#ifndef BUFFER_H
#define BUFFER_H

#include <FastLED.h>
// #include <functional>
// #include <ESP8266WebServer.h>

class Buffer {
public:
    // typedef std::function<void()> BufferDidChange;
    uint16_t width;
    uint16_t height;
    uint16_t numberOfLeds;
    CRGB* leds;

    Buffer(uint16_t _width, uint16_t _height);
    ~Buffer();

    void fill(CRGB color);
    void set(CRGB color, uint16_t x, uint16_t y);
private:
    void invokeBufferDidChanged();
};

#endif