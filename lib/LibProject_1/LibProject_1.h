#ifndef LIB_PROJECT_1
#define LIB_PROJECT_1

#include "LibOledI2c.h"
#include <ESP32Servo.h>
//#include <LibEsp32Servo.h>

#include "RTClib.h"

#define CLK 5
#define DT 25
#define SW 26

#define INSOLE_1 18
#define INSOLE_2 19

/*
    ANGLE one Insole
    ANGLEMAX 98
    ANGLEMIN 60
    ANGLETB 77
*/ 

// ANGLE many Insole
#define ANGLEMAX 103   // Trai
#define ANGLEMIN 65   // Phai
#define ANGLETB 83
#define SPEED 4

#define SERVO 4

class LibProject_1
{
private:
    /* data */
   
    LibOledI2c libolei2c;
    //LibEsp32Servo libesp32servo;
    RTC_DS1307 rtc;
    Servo myservo;

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
    uint16_t data = 0;

    uint16_t count1 = 0;
    uint16_t dem1 = 0;
    uint16_t dem2 = 0;

    uint8_t stateStart2 = 0;
    uint8_t statePause2 = 0;
    uint8_t stateStop2 = 0;

    uint8_t stateStart1 = 0;
    uint8_t statePause1 = 0;
    uint8_t stateStop1 = 0;

    uint16_t tempRun = 0;
    uint16_t ul = 0;

    uint16_t countInsole_1_2 = 0;
    uint16_t countInsole_2_2 = 0;
    
    uint16_t countInsole_1_1 = 0;
    uint16_t countInsole_2_1 = 0;

    LibProject_1(/* args */);

    void setServo();
    void setServoTB();

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