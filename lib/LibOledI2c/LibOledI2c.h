#ifndef LIB_OLED_I2C
#define LIB_OLED_I2C

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO

static const unsigned char PROGMEM logo16_glcd_bmp[] = { 0xff, 0xf0, 0xfd, 0xf0, 0xf8, 0xf0, 0xf8, 0xf0, 0xf8, 0x70, 0x9a, 0x70, 0xdf, 0x30, 0xcf, 0x30,
                                                         0xed, 0x90, 0xe1, 0x90, 0xf1, 0xf0, 0xf3, 0xf0, 0xfb, 0xf0, 0xff, 0xf0 };

static const unsigned char PROGMEM logo[] = { 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xf1, 0xff, 0xff, 0xe1, 0xff, 0xff,
                                              0xe0, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xc0, 0x7f, 0xff, 0x80, 0x7f, 0x87, 0x80, 0x3f, 0xc7, 0xc4,
                                              0x3f, 0xc3, 0xce, 0x1f, 0xe3, 0xee, 0x1f, 0xe1, 0xff, 0x0f, 0xf1, 0xff, 0x0f, 0xf0, 0xff, 0x87,
                                              0xf8, 0x7f, 0x87, 0xf8, 0x77, 0xc3, 0xfc, 0x33, 0xc3, 0xfc, 0x23, 0xe1, 0xfe, 0x03, 0xff, 0xfe,
                                              0x03, 0xff, 0xff, 0x07, 0xff, 0xff, 0x87, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xcf, 0xff, 0xff, 0xdf,
                                              0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };


class LibOledI2c
{
private:
    /* data */
    

public:
    
    Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    LibOledI2c(/* args */);
    void begin();

    void printTriangle(uint8_t st);
    void printTargetset(int16_t countTargetset);
    void targetCount(uint8_t x, uint8_t y, uint16_t valuelast, uint16_t value);
    void printCountTarget1(int16_t demTarget);
    void printCountTarget2(int16_t demTarget);
    void printInsole_1(uint16_t countIns1);
    void printInsole_2(uint16_t countIns2);
    void printM_D_H_M(uint8_t x, uint8_t y, uint16_t lastValue, uint16_t value); // Print Month or Day or Hour or Minutes


    //~LibOledI2c();
};

// LibOledI2c::LibOledI2c(/* args */)
// {
// }

// LibOledI2c::~LibOledI2c()
// {
// }


#endif