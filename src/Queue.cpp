#include <Arduino.h>
#include <freertos/FreeRTOS.h>

#define Threshold 40 
touch_pad_t touchPin;
void Task1(void* pvParameters);
void Task2(void* pvParameters);
void callback(){
  //placeholder callback function
}
void Task1(void* Paramter) {
  //for(;;) {
    Serial.println("Task1");
    //vTaskDelay(1000);
  //}
}

void Task2(void* Paramter) {
  //for(;;) {
    Serial.println("Task2");
    Serial.println("Going to sleep now");
  esp_deep_sleep_start();
  Serial.println("This will never be printed");
    //vTaskDelay(2000);

  //}
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  touchAttachInterrupt(T3, callback, Threshold);
  xTaskCreatePinnedToCore(Task1,"Task1",1024,NULL,1,NULL,0);
  xTaskCreatePinnedToCore(Task2,"Task2",10000,NULL,1,NULL,1);
  

//   Configure Touchpad as wakeup source
  esp_sleep_enable_touchpad_wakeup();

  //Go to sleep now
//   Serial.println("Going to sleep now");
//   esp_deep_sleep_start();
//   Serial.println("This will never be printed");
}

void loop() {
  // put your main code here, to run repeatedly:
  vTaskDelete(NULL);
}