#include<stdio.h>
#include<string.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include  "esp_system.h"
#include "esp_log.h"
#define TAG  "BLINKER"
#define pin 2
char c;
void app_main(void){
gpio_set_direction(pin,GPIO_MODE_OUTPUT);
while(1){
   c=getchar();

if(c!=  0xff){
    if(c=='A'){
    gpio_set_level(pin,1);
ESP_LOGI(TAG,"the led is on %d",pin);
    }
    else if (c=='a'){ 
        gpio_set_level(pin,0);
        ESP_LOGI(TAG,"the led is off %d",pin);
        
    }

    vTaskDelay(100);
}
}
}
