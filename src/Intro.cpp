#include <Arduino.h>
#include <freertos/FreeRTOS.h>


void Task1(void* pvParameters);
void Task2(void* pvParameters);

void Task1(void* Paramter) {
  for(;;) {
    Serial.println("Task1");
    vTaskDelay(1000);
  }
}

void Task2(void* Paramter) {
  for(;;) {
    Serial.println("Task2");
    vTaskDelay(2000);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  xTaskCreatePinnedToCore(Task1,"Task1",1024,NULL,1,NULL,0);
  xTaskCreatePinnedToCore(Task2,"Task2",1024,NULL,1,NULL,1);
}

void loop() {
  // put your main code here, to run repeatedly:
  vTaskDelete(NULL);
}