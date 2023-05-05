#include <LibNeoPixel.h>

LibNeoPixel::LibNeoPixel()  {

}

void LibNeoPixel::begin() {
    pixels.begin();
}

void LibNeoPixel::setUp() {

}

void LibNeoPixel::setBright(uint8_t brightNess) {
    pixels.setBrightness(brightNess);
}

void LibNeoPixel::showPixel(uint8_t pinLed, uint8_t pRed, uint8_t pGreen, uint8_t pBlue) {
    pixels.setPixelColor(pinLed, pixels.Color(pRed, pGreen, pBlue));
    pixels.show();
}