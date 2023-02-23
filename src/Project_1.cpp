#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <freertos/FreeRTOS.h>

#include "LibWiFi.h"
#include "LibNeoPixel.h"
#include "LibProject_1.h"


const char* WIFI_SSID = "iPhone của Sơn";
const char* WIFI_PASSWORD = "esp32rtos";

#define FIREBASE_HOST "exampletest-a2b25-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "8IYQWktZVOLIVFN0cI4Lbu62DyWdAyPoqRdjlVDf"

TaskHandle_t task_test_1;
TaskHandle_t task_test_2;
TaskHandle_t task_menu;
TaskHandle_t task_option;
TaskHandle_t task_data_firebase;

LibWiFi libwifi;
LibNeoPixel libneopixel;
LibProject_1 libproject_1;

void task_Menu(void* Parameters) {
    vTaskSuspend(task_option);
    libproject_1.screenMenu();
    vTaskResume(task_option);
    vTaskDelete(NULL);
}

void test_1(void* Parammeters) {
    vTaskSuspend(task_option);
    libproject_1.screenTest1();
    vTaskResume(task_option);
    vTaskDelete(NULL);
}

void test_2(void* Parameters) {
    vTaskSuspend(task_option);
    libproject_1.screenTest2();
    vTaskResume(task_option);
    vTaskDelete(NULL);
}

void task_Option(void* Parameters) {
    for (;;) {
        switch (libproject_1.stateMH)
        {
            case 0:
                /* code */
                xTaskCreatePinnedToCore(task_Menu, "task_Menu", 4000, NULL, 2, &task_menu, 0);
                break;
            case 1:
                Serial.println("test1");
                xTaskCreatePinnedToCore(test_1, "test_1", 4000, NULL, 2, &task_test_1, 0);
                break;
            case 2:
                xTaskCreatePinnedToCore(test_2, "test_2", 4000, NULL, 2, &task_test_2, 0);
                break;
            default:
                break;
        }
    }
}
uint32_t lastTimeA = millis();
uint32_t lastTimeB = millis();
uint32_t lastTimeC = millis();
uint32_t lastTimeD = millis();
void task_Data_Firebase(void* Paramters) {
    for(;;) {

        switch (libproject_1.stateMH)
        {
        case 1:
            /* code */
            //set data test 1 to firebase
            if(millis() - lastTimeA > 1000) {
                libwifi.sendIntdata("/data1", libproject_1.count1);
                libwifi.sendIntdata("/datacount1R", libproject_1.countInsole_1_1);
                libwifi.sendIntdata("/datacount1L", libproject_1.countInsole_2_1);

        
                float ml = (float) libproject_1.dem1/libproject_1.data * 100.0;
                int ap = (int)ml;
                libwifi.sendIntdata("/countdata1",libproject_1.dem1);
                libwifi.sendIntdata("/data",ap);
                lastTimeA = millis();
            }
            libproject_1.stateStart1 = (libwifi.getStrdata("/btnStart1")).toInt();Serial.println(libproject_1.stateStart1);
            libproject_1.statePause1 = (libwifi.getStrdata("/btnPause1")).toInt();Serial.println(libproject_1.statePause1);
            libproject_1.stateStop1 = (libwifi.getStrdata("/btnStop1")).toInt();Serial.println(libproject_1.stateStop1);
            if(millis() - lastTimeC > 300) {
                libwifi.sendStrdata("/btnStart1", String(libproject_1.stateStart1));
                libwifi.sendStrdata("/btnPause1", String(libproject_1.statePause1));
                libwifi.sendStrdata("/btnStop1", String(libproject_1.stateStop1));
                lastTimeC = millis();
            }
            break;
        case 2:
            //set data test 2 to firebase
            if(millis() - lastTimeB > 1000) {
                libwifi.sendIntdata("/countdata2", libproject_1.dem2);
                libwifi.sendIntdata("/runtimeH", libproject_1.ul);
                libwifi.sendIntdata("/runtimeM", libproject_1.tempRun);

                libwifi.sendIntdata("/datacount2R", libproject_1.countInsole_1_2);
                libwifi.sendIntdata("/datacount2L", libproject_1.countInsole_2_2);
                lastTimeB = millis();
            }
            libproject_1.stateStart2 = (libwifi.getStrdata("/btnStart2")).toInt();
            libproject_1.statePause2 = (libwifi.getStrdata("/btnPause2")).toInt();
            libproject_1.stateStop2 = (libwifi.getStrdata("/btnStop2")).toInt();
            if(millis() - lastTimeD > 300) {
                libwifi.sendStrdata("/btnStart2", String(libproject_1.stateStart2));
                libwifi.sendStrdata("/btnPause2", String(libproject_1.statePause2));
                libwifi.sendStrdata("/btnStop2", String(libproject_1.stateStop2));
            }
        default:
            Serial.println("hello");
            break;
        }
        //libproject_1.countT = (libwifi.getStrdata("/data1")).toInt();
        
    }
}

void setup() {

    Serial.begin(115200);
    //liboledi2c.begin();
    libwifi.setupWiFi(WIFI_SSID, WIFI_PASSWORD);

    libwifi.setupFB(FIREBASE_AUTH, FIREBASE_HOST);
    Serial.println("Ok");
    
    libproject_1.begin();
    libproject_1.screenIntro();
    // Serial.println("Oke");

    xTaskCreatePinnedToCore(task_Data_Firebase, "task_Data", 15000, NULL, 3, &task_data_firebase, 1);
    xTaskCreatePinnedToCore(task_Option, "task_Option", 5000, NULL, 1, &task_option, 0);
    

    //xTaskCreatePinnedToCore(test_1, "test_1", 5000, NULL, 1, &task_test_1, 1);
    //xTaskCreatePinnedToCore(test_2, "test_2", 5000, NULL, 1, &task_test_2, 1);
    //xTaskCreatePinnedToCore();
}

void loop() {
    vTaskDelete(NULL);
}