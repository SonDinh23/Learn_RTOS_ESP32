#ifndef LIB_NEO_PIXEL
#define LIB_NEO_PIXEL

#include <Adafruit_NeoPixel.h>

#define PIN_RGB_LED 32

// const int NUMBER_PIN_LED 1; // if using 1  led, value using 1  



class LibNeoPixel
{
private:
    /* data */
    Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN_RGB_LED, NEO_GRB + NEO_KHZ800);

public:
    LibNeoPixel(/* args */);
    // ~LibNeoPixel();
    void begin();
    void setUp();
    void setBright(uint8_t brightNess);
    void showPixel(uint8_t pinLed, uint8_t pRed, uint8_t pGreen, uint8_t pBlue);
};

// LibNeoPixel::LibNeoPixel(/* args */)
// {
// }

// LibNeoPixel::~LibNeoPixel()
// {
// }


#endif