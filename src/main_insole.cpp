#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <freertos/FreeRTOS.h>

#include "LibWiFi.h"
#include "LibNeoPixel.h"
#include "LibProject_1.h"

//char *WIFI_SSID = "Vulcan Hall Of Fame";

char WIFI_SSID[] = "Vulcan Augmetics";                       // Wifi Address
char WIFI_PASSWORD[] = "wearevulcan.com";                    // Key Wifi

String addrOnServer = "Machine Test Insole/";               // Test tool address
String addrIdServer = "I0001/";                             // The test suite's ID address
String addrLogicServer = "Logic/";                          // Test suite logic levels
String addrDataServer = "Data/";                            // The data of the test suite
String addrTest1Server = "Test1/";                          // Test 1 address
String addrTest2Server = "Test2/";                          // Test 2 address

#define FIREBASE_HOST "exampletest-a2b25-default-rtdb.firebaseio.com"   // Firebase address
#define FIREBASE_AUTH "8IYQWktZVOLIVFN0cI4Lbu62DyWdAyPoqRdjlVDf"        // Key firebase

TaskHandle_t task_encoder;
TaskHandle_t task_test_1;
TaskHandle_t task_test_2;
TaskHandle_t task_menu;
TaskHandle_t task_option;
TaskHandle_t task_button_encoder;
TaskHandle_t task_data_firebase;

LibWiFi libwifi;
LibNeoPixel libneopixel;
LibProject_1 libproject_1;

bool isTheFirstDisplay(int);
void sendData();
void sendDataReset();
int16_t checkCouter(int16_t);

bool stateTemp = false;
int8_t chieuxoay = 0;
static bool stateFirstset = true;
// int8_t oldStateMH = 0;

uint32_t lastTimeOnServerTest1 = millis();
uint32_t lastTimeOnServerTest2 = millis();

uint32_t lastTimeStop = millis();
uint8_t countStop = 0;
bool stateTT = false;
bool startState = false;

bool key = false;
bool keyReturn = false;
bool keyStart = false;
bool keyPause = false;
bool keyStop = false;

void task_Menu(void *Parameters)
{
    vTaskSuspend(task_menu);
    for (;;) {
        libproject_1.screenMenu();
        vTaskDelay(100);
    }
}

void test_1(void *Parammeters)
{
    
    vTaskSuspend(task_test_1);
    for(;;) {
        libproject_1.screenTest1();
        vTaskDelay(30);
    }
}

void test_2(void *Parameters)
{
    vTaskSuspend(task_test_2);
    for (;;) {
        libproject_1.screenTest2();
        vTaskDelay(30);
    }
}

void task_Option(void *Parameters)
{
    for (;;)
    {
        switch (libproject_1.getStateOnServerMenu())
        {
            case 0:
                // Serial.println("testmenu");
                vTaskSuspend(task_test_1);
                vTaskSuspend(task_test_2);
                if (isTheFirstDisplay(0)) libproject_1.setFirstScreen(true);

                stateTemp = true;
                vTaskResume(task_menu);
                break;
            case 1:
                // Serial.println("test1");
                vTaskSuspend(task_menu);
                vTaskSuspend(task_test_2);
                if (isTheFirstDisplay(1)) libproject_1.setFirstScreen(true);
                stateTemp = false;
                vTaskResume(task_test_1);
                break;
            case 2:
                // Serial.println("test2");
                vTaskSuspend(task_menu);
                vTaskSuspend(task_test_1);
                if (isTheFirstDisplay(2)) libproject_1.setFirstScreen(true);
                stateTemp = false;
                vTaskResume(task_test_2);
                break;
            default:
                break;
        }

        vTaskDelay(10);
    }
}

void task_Encoder(void* Parameters) {
    int8_t _chieuxoay;
    for (;;) {
        libproject_1.readTriangle();
        
        _chieuxoay = libproject_1.updateEncoder();
        chieuxoay = _chieuxoay != 0 ? _chieuxoay : chieuxoay;
        // Serial.println(chieuxoay);
        vTaskDelay(1);
    }
}

int dataProgressbar = 0;
float tempProgressbar = 0;
int16_t tempCount = 0;
static uint16_t tempCountSv = 0;
static int16_t lastcheck = 0;
void task_Data_Firebase(void *Paramters)
{
    // libwifi.sendStrdata(addrOnServer + addrIdServer + addrLogicServer + "state", "2");
    // libwifi.sendStrdata(addrOnServer + addrIdServer + addrLogicServer + "stateMenu", "0");
    // libwifi.sendStrdata(addrOnServer + addrIdServer + addrDataServer + addrTest1Server + "data1", "0");
    for (;;)
    {   

        if (stateTemp == true) {
            libproject_1.getTriangle();
            while (libproject_1.getButton() == 0) {
                stateTT = true;
                vTaskDelay(5);
            }
            if (stateTT) { 
                libproject_1.setStateOnServerMenu(libproject_1.stateTriangle());
                libproject_1.setStateOnServer(2);
                libproject_1.setStatePause(true);
                libproject_1.setCounter(0);
                stateTT = false;
            }
        }else {
            sendData();
            if (libproject_1.getStateStart()) {
                tempCount += chieuxoay * 100;
                if (tempCount < 0) {
                    tempCount = 0;
                    libproject_1.setCounter(0);
                }
                chieuxoay = 0;
                Serial.println(tempCount);
                libproject_1.printTargetSet(tempCount);
                libproject_1.setTargetSetTest1(tempCount);
                while (libproject_1.getButton() == 0) {
                    startState = true;
                    vTaskDelay(5);
                }
                if (startState) {
                    vTaskDelay(100);
                    libproject_1.setStateOnServer(1);
                    libproject_1.setStateStart(false);
                    startState = false;
                }
                vTaskDelay(5);
            }else {
                while (libproject_1.getButton() == 0) {
                    if (millis() - lastTimeStop > 1000) {
                        countStop++;
                        Serial.println(countStop);
                        lastTimeStop = millis();
                    }
                    vTaskDelay(5);
                }
                if (countStop > 3) {
                    libproject_1.setStateOnServerMenu(0);
                    libproject_1.setStateOnServer(0);
                    libproject_1.setStateStart(true);
                    countStop = 0;
                }else if(countStop > 0 && countStop < 5 ) {
                    if (libproject_1.getStatePause()) {
                        libproject_1.setStateOnServer(-1);
                        libproject_1.setStatePause(false);
                        countStop = 0;
                        vTaskDelay(5);
                    }else {
                        libproject_1.setStateOnServer(1);
                        keyStop = true;
                        libproject_1.setStatePause(true);
                        countStop = 0;
                        vTaskDelay(5);
                    }
                }
                if (libproject_1.getStateCountT()) {
                    Serial.println("xong");
                    libproject_1.setStateOnServer(2);
                    libproject_1.setStateStart(true);
                    libproject_1.setStateCountT(false);
                }    
                  
            }
        }
        if (libproject_1.getStateCountT()) {
            libproject_1.setStateCountT(false);
        }
        vTaskDelay(1);
    }
}

void setup() {

    Serial.begin(115200);
    libwifi.setupWiFi(WIFI_SSID, WIFI_PASSWORD);

    libwifi.setupFB(FIREBASE_AUTH, FIREBASE_HOST);
    Serial.println("Ok");

    libproject_1.begin();
    libproject_1.screenIntro();
    delay(500);

    xTaskCreatePinnedToCore(task_Data_Firebase, "task_Data", 20000, NULL, 7, &task_data_firebase, 0);
    xTaskCreatePinnedToCore(task_Encoder, "task_encoder", 5000, NULL, 8, &task_encoder, 1);
    xTaskCreatePinnedToCore(test_1, "test_1", 7000, NULL, 2, &task_test_1, 1);
    xTaskCreatePinnedToCore(test_2, "test_2", 7000, NULL, 2, &task_test_2, 1);
    xTaskCreatePinnedToCore(task_Menu, "task_Menu", 7000, NULL, 2, &task_menu, 1);
    xTaskCreatePinnedToCore(task_Option, "task_Option", 10000, NULL, 1, &task_option, 1);

    
}
void loop() {
    vTaskDelete(NULL);
}

bool isTheFirstDisplay(int _sate) {
    static int8_t oldStateMH = -1;
    
    if (oldStateMH != _sate) {

        Serial.print(oldStateMH); 
        Serial.print("\t"); 
        Serial.println(_sate); 

        oldStateMH = _sate;
        return true;
    }
    else return false;
}

void sendData() {
    switch (libproject_1.getStateOnServerMenu())
        {
            case 1:
                {
                    if (millis() - lastTimeOnServerTest1 > 20000) {
                        if(libproject_1.getTargetSetTest1() != 0) {
                            tempProgressbar = (float)libproject_1.dem1 / libproject_1.getTargetSetTest1() * 100.0;
                            dataProgressbar = (int)tempProgressbar;
                            libwifi.sendIntdata(addrOnServer + addrIdServer + addrDataServer + addrTest1Server + "data progressbar", dataProgressbar);
                        }else {
                            libwifi.sendIntdata(addrOnServer + addrIdServer + addrDataServer + addrTest1Server + "data progressbar", 0);
                        }
                        libwifi.sendIntdata(addrOnServer + addrIdServer + addrDataServer + addrTest1Server + "countdata1", libproject_1.dem1);
                        lastTimeOnServerTest1 = millis();
                    }
                    break;
                }
            case 2: 
                {
                    if (millis() - lastTimeOnServerTest2 > 20000) {
                        libwifi.sendIntdata(addrOnServer + addrIdServer + addrDataServer + addrTest2Server + "countdata2", libproject_1.dem2);
                        libwifi.sendIntdata(addrOnServer + addrIdServer + addrDataServer + addrTest2Server + "runtimeH", libproject_1.ul);
                        libwifi.sendIntdata(addrOnServer + addrIdServer + addrDataServer + addrTest2Server + "runtimeM", libproject_1.tempRun);
                        libwifi.sendIntdata(addrOnServer + addrIdServer + addrDataServer + addrTest2Server + "datacount2R", libproject_1.countInsole_1_2);
                        libwifi.sendIntdata(addrOnServer + addrIdServer + addrDataServer + addrTest2Server + + "datacount2L", libproject_1.countInsole_2_2);
                        lastTimeOnServerTest2 = millis();
                    }
                    break;
                }
            default:
                break;
        }
}

void sendDataReset() {
    if (libproject_1.stateSend == true) {
            libwifi.sendStrdata(addrOnServer + addrIdServer + addrLogicServer + "state", "2");
            libwifi.sendStrdata(addrOnServer + addrIdServer + addrLogicServer + "stateMenu", "0");
            libwifi.sendIntdata(addrOnServer + addrIdServer + addrDataServer + addrTest1Server + "data progressbar", 0);
            libwifi.sendIntdata(addrOnServer + addrIdServer + addrDataServer + addrTest1Server + "countdata1", 0);
            

            libwifi.sendIntdata(addrOnServer + addrIdServer + addrDataServer + addrTest2Server + "countdata2", 0);
            libwifi.sendIntdata(addrOnServer + addrIdServer + addrDataServer + addrTest2Server + "runtimeH", 0);
            libwifi.sendIntdata(addrOnServer + addrIdServer + addrDataServer + addrTest2Server + "runtimeM", 0);

            libwifi.sendIntdata(addrOnServer + addrIdServer + addrDataServer + addrTest2Server + "datacount2R", 0);
            libwifi.sendIntdata(addrOnServer + addrIdServer + addrDataServer + addrTest2Server + + "datacount2L", 0);
            libproject_1.stateSend = false;
        }
}

int16_t checkCouter(int16_t num) {
    static int16_t lastNum = 0;
    if (num != lastNum) {
        lastNum = num;
        return lastNum;
    }
    return 0;
}
