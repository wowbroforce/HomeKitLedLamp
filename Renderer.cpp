#include "Renderer.h"

void Renderer::setup(Buffer *_buffer) {
    if (_buffer == NULL) Serial.println("Renderer::setup(Buffer* _buffer), _buffer == NULL"); return;
    if (_buffer->leds == NULL) Serial.println("Renderer::setup(Buffer* _buffer), _buffer->leds == NULL"); return;
    buffer = _buffer;
    // buffer->bufferDidChanged = invokeBufferDidChanged;
    FastLED.addLeds<WS2812B, LED_PIN, COLOR_ORDER>(buffer->leds, buffer->numberOfLeds)/*.setCorrection( TypicalLEDStrip )*/;
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clear();
    if (CURRENT_LIMIT > 0) FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
};

void Renderer::update() {
    if (isRendered) return;
    FastLED.show();
    isRendered = true;
}

inline void Renderer::bufferDidChanged(){};
