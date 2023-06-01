#include<stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void task1(){
    
    while(1){
        printf("hi");
    }
    vTaskDelay(100);
}
        void task2(){
    
    while(1){
        printf("hello");
    }
        vTaskDelay(100);
        vTaskDelete(NULL);
}
void app_main(void){
xTaskCreate(task1,"task1",2048,NULL,1,NULL);
xTaskCreate(task2,"task2",2048,NULL,1,NULL);
}