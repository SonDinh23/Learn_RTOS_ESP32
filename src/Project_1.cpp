#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <freertos/FreeRTOS.h>

#include <LibWiFi.h>
#include <LibNeoPixel.h>
#include <LibProject_1.h>

const char* WIFI_SSID = "iPhone của Sơn";
const char* WIFI_PASSWORD = "esp32rtos";

#define FIREBASE_HOST "exampletest-a2b25-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "8IYQWktZVOLIVFN0cI4Lbu62DyWdAyPoqRdjlVDf"


TaskHandle_t task_test_1;
TaskHandle_t task_test_2;
TaskHandle_t task_menu;
TaskHandle_t task_data_firebase;

LibWiFi libwifi;
LibNeoPixel libneopixel;
LibProject_1 libproject_1;


void Test_1(void* Parammeters) {
    vTaskSuspend(task_test_1);
    for(;;) {

    }
}

void Test_2(void* Parameters) {
    vTaskSuspend(task_test_2);
    for(;;) {

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
    Serial.println("Oke");
    //liboledi2c.printTriangle(1);
    // libeopixel.begin();
    // libneopixel.showPixel(0,150,150,150);

    // xTaskCreatePinnedToCore();
    // xTaskCreatePinnedToCore();
    // xTaskCreatePinnedToCore();
    // xTaskCreatePinnedToCore();
}
void loop() {
    vTaskDelete(NULL);
}