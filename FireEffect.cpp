#include "FireEffect.h"

FireEffect::FireEffect(uint16_t _width, uint16_t _height) {
    width = _width;
    height = _height;
    
    buffer = new Buffer(width, height);
    firePixels = new uint8_t*[height];
    for (uint16_t i = 0; i < height; i++) {
        firePixels[i] = new uint8_t[width];
        for (uint16_t j = 0; j < width; j++) {
            firePixels[i][j] = 0;
        }
    }
    setFireSourceStrength(255);
    srand(time(NULL));
}

FireEffect::~FireEffect() {
    for (uint16_t i = 0; i < height; ++i) {
        delete[] firePixels[i];
    }
    delete[] firePixels;
    delete buffer;
}

void FireEffect::setFireSourceStrength(uint8_t strength) {
    for (uint16_t j = 0; j < width; ++j) {
        firePixels[height - 1][j] = strength;
    }
}

void FireEffect::update() {
    uint8_t decay;
    int16_t newFireValue;

    for (uint16_t i; i < width; ++i) {
        for (uint16_t j; j < height; ++j) {
            decay = (rand() % 3);

            int32_t newJ = j - decay + 1;
            newJ = newJ < 0 ? width - 1 : newJ;
            newJ = newJ >= width ? 0 : newJ;

            newFireValue = firePixels[i + 1][j] - (decay & 1);

            firePixels[i][newJ] = newFireValue < 0 ? 0 : newFireValue;
        }
    }
}

void FireEffect::writeToBuffer() {
    
}
