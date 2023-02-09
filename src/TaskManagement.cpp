#include <Arduino.h>
#include <freertos/FreeRTOS.h>

// void Task1(void* pvParameters);
// void Task2(void* pvParameters);

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;

int counter = 0;

void Task1(void* Paramter) {
    TickType_t getTick; // lấy giá trị thời gian thực esp32
    getTick = xTaskGetTickCount();
    for(;;) {
        Serial.println("Task 1");
        counter++;
        if(counter == 15) {
            vTaskResume(TaskHandle_2);
        }
        vTaskDelayUntil(&getTick, 1000/portTICK_PERIOD_MS);
    }
}

void Task2(void* Paramter) {
    for(;;) {
        Serial.println("Task 2");
        counter++;
        if(counter == 10) {
            vTaskSuspend(TaskHandle_2);
            //Serial.println("oke");
        }
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void setup() {
    Serial.begin(115200);
    xTaskCreatePinnedToCore(Task1,"Print1",1024,NULL,1,&TaskHandle_1,0);
    xTaskCreatePinnedToCore(Task2,"Print2",1024,NULL,1,&TaskHandle_2,1);
}
void loop() {
    vTaskDelete(NULL);
}