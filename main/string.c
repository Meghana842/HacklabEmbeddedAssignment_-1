#include<strings.h>
#include<stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
void app_main(void){
    
    while(1){
        char str[10];
    gets(str);
    scanf("%s",str);
    printf("%s",str);
    vTaskDelay(100);
    
    }
    
}