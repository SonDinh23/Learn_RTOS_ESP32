#ifndef LIB_PROJECT_1
#define LIB_PROJECT_1

#include <LibOledI2c.h>
#include <LibEsp32Servo.h>

#include "RTClib.h"

#define CLK 5
#define DT 25
#define SW 26

#define INSOLE_1 18
#define INSOLE_2 19

class LibProject_1
{
private:
    /* data */
   
    LibOledI2c libolei2c;
    LibEsp32Servo libesp32servo;
    RTC_DS1307 rtc;

    uint8_t stateTG = 1;

    int16_t counter = 0;
    int currentStateCLK;
    int lastStateCLK;
    String currentDir = "";
    unsigned long lastButtonPress = 0;

    uint16_t countInsole_1 = 0;
    uint16_t countInsole_2 = 0;

    uint8_t m = 0;
    uint8_t n = 0;

    uint8_t stateInsoleError = 0;

    uint8_t thangStr = 0;
    uint16_t ngayStr = 0;
    uint16_t gioStr = 0;
    uint16_t phutStr = 0;

    uint8_t runGio = 0;
    uint8_t runPhut = 0;

    uint8_t thang = 0;
    uint8_t ngay = 0;
    uint8_t gio = 0;
    uint8_t phut = 0;

    int8_t strThang = -1;
    int8_t strNgay = -1;
    int8_t strGio = -1;
    int8_t strPhut = -1;

    uint8_t lastRunGio = -1;
    uint8_t lastRunPhut = -1;
    
public:
    uint8_t stateMH = 0;
    LibProject_1(/* args */);

    //print many screen
    void screenIntro();
    void screenMenu();
    void screenTest1();
    void screenTest2();

    void begin();
    uint8_t updateEncoder();
    uint16_t testInsole_1();
    uint16_t testInsole_2();
    void printRtcNow(uint8_t month, uint8_t day, uint8_t hour, uint8_t minute);
    void printRtcStart(uint8_t month, uint8_t day, uint8_t hour, uint8_t minute);
    void printRunTime(uint8_t hour, uint8_t minute);

};

// LibProject_1::LibProject_1(/* args */)
// {
// }




#endif