#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#define gpio1  2
#define gpio2 34
void app_main(void)
{
gpio_set_direction(gpio1,GPIO_MODE_OUTPUT);
gpio_set_direction(gpio2,GPIO_MODE_INPUT);
while(1){
    if(gpio_get_level(gpio2)==0){
        gpio_set_level(gpio1,1);
    
    }
  else
        gpio_set_level(gpio1,0);
}
vTaskDelay(1);
}
