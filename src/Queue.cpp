#include <Arduino.h>
#include <freertos/FreeRTOS.h>

TaskHandle_t Task1;
TaskHandle_t Task2;
TaskHandle_t Task3;
TaskHandle_t Task4;

void Task1(void* Parameters) {

}

void Task2(void* Parameters) {

}

void Task3(void* Parameters) {

}

void Task4(void* Parameters) {

}

void setup() {
    Serial.begin(115200);
    Serial.println("ok");
    xTaskCreatePinnedToCore(Task1,"Task1",128,);

}
void loop() {

}