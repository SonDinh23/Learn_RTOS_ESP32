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
#define ANGLEMAX    96   // Trai
#define ANGLEMIN    80      // Phai
#define ANGLETB     92
#define SPEED       12

#define SERVO_1     4
#define SERVO_2     27
#define SERVO_3     32
#define SERVO_4     33

class LibProject_1
{
private:
    /* data */
   
    LibOledI2c libolei2c;
    //LibEsp32Servo libesp32servo;
    RTC_DS1307 rtc;

    Servo myservo_1;
    Servo myservo_2;
    Servo myservo_3;
    Servo myservo_4;

    uint8_t stateTG = 1;
    int8_t rotation = 0;
    uint8_t tamgiac;
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

    // uint16_t timeStr[4];
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

    DateTime now;

    uint16_t tempTime = 0;
    uint16_t tempTimeStart = 0;
    uint16_t tempTimeNow = 0;
    uint16_t tempTimePause = 0;

    uint16_t minutesPause = 0;
    uint16_t hourPause = 0;
    uint16_t dayPause = 0;
    
    uint16_t nowDay = 0;
    uint16_t nowHour = 0;
    uint16_t nowMinute = 0;

    uint16_t tempPause = 0;
    uint16_t tempPause2 = 0;

    uint16_t targetSetTest1 = 0;
    bool printTargetFirst = true;

    uint16_t lastTarget = 0;
    bool stateTset = true;
    bool stateChangeSend = false;

    uint8_t stateButton = 0;

    int8_t stateOnServer;
    int8_t stateOnServerMenu = 0;

    bool stateStart = true;
    bool statePause = true;
    bool stateStop = false;

    bool tbServo = true;
public:
    
    // uint16_t data = 0;

    uint16_t countT = 0;
    uint16_t count1 = 0;
    uint16_t dem1 = 0;
    uint16_t dem2 = 0;

    
    
    bool firstState = true;

    bool stateSend = false;

    uint16_t tempRun = 0;
    uint16_t ul = 0;

    uint16_t countInsole_1_2 = 0;
    uint16_t countInsole_2_2 = 0;
    
    uint16_t countInsole_1_1 = 0;
    uint16_t countInsole_2_1 = 0;

    LibProject_1(/* args */);

    void setFirstScreen(bool state);

    void setServo();
    void setServoTB();

    //print many screen
    void screenIntro();
    void screenMenu(); //TaskHandle_t _op
    void screenTest1();
    void screenTest2();

    void firstTest1();
    void firstTest2();

    void begin();
    int8_t updateEncoder();
    uint16_t testInsole_1();
    uint16_t testInsole_2();
    void printRtcNow(uint8_t month, uint8_t day, uint8_t hour, uint8_t minute);
    void printRtcStart(uint8_t month, uint8_t day, uint8_t hour, uint8_t minute);
    void printRunTime(uint8_t hour, uint8_t minute);

    void setTargetSetTest1(uint16_t data);
    uint16_t getTargetSetTest1();
    void printTargetSet(uint16_t _data);
    uint16_t getDem1();
    uint16_t getDem2();
    void updateTime();
    bool getStateCountT();
    void setStateCountT(bool _data);

    int8_t getStateOnServerMenu();
    int8_t getStateOnServer();
    void setStateOnServerMenu(int8_t _data);
    void setStateOnServer(int8_t _data);
    uint8_t getButton();
    
    uint8_t stateTriangle();
    void getTriangle();
    void readTriangle();

    int16_t getCounter();
    void setCounter(int8_t _data);

    void setStateStart(bool _state);
    void setStatePause(bool _state);
    void setStateStop(bool _state);

    bool getStateStart();
    bool getStatePause();
    bool getStateStop();

    bool getStateSend();
    void setStateSend(bool _data);
};


#endif