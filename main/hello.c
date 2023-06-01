#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
//#include "led_strip.h"
#include "sdkconfig.h"
#include "esp_system.h"



#define EMR_SAF 27
#define ALR_SAF 19
#define O_TR 32
#define O_FR 25
#define O_LR 33
#define O_EX 14
#define N_RE 13
#define REV 39
#define AUX 2
#define FRK_DET 35
#define I_SB 36
#define red_tower 27
#define yellow_tower 17
#define green_tower 22
#define buzz_tower 14
#define TAG "TESTER"
  int prev_rev = -1;
int prev_aux = -1;
int prev_frk_det = -1;
int prev_i_sb= -1; 

char chr;
/* Use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
static void configure_gpio_output(int gpio)
{
    ESP_LOGI(TAG,"CONFIGURE FOR GPIO %d",gpio);
    esp_rom_gpio_pad_select_gpio(gpio);
    gpio_set_direction(gpio,GPIO_MODE_OUTPUT);
}

static void configure_gpio_input(int gpio)
{
    ESP_LOGI(TAG,"CONFIGURE FOR GPIO %d",gpio);
    esp_rom_gpio_pad_select_gpio(gpio);
    gpio_set_direction(gpio,GPIO_MODE_INPUT);
}

void relay_ctrl(){

        chr = getchar();
        if(chr != 0xff && chr != '\n'){
                if(chr == 'F'){
                        gpio_set_level(O_FR,1);
                        ESP_LOGI(TAG,"FORK RELAY IS ON");
                }
                        else if(chr == 'f'){
                        gpio_set_level(O_FR,0);
                        ESP_LOGI(TAG,"FORK RELAY IS OFF");
                }
                else if(chr == 'T'){
                        gpio_set_level(O_TR,1);
                        ESP_LOGI(TAG,"TURTLE RELAY IS ON");
                }
                else if(chr == 't'){
                        gpio_set_level(O_TR,0);
                        ESP_LOGI(TAG,"TURTLE RELAY IS OFF");
                }
                else if(chr == 'L'){
                        gpio_set_level(O_LR,1);
                        ESP_LOGI(TAG,"LED RELAY IS ON");
                }
                else if(chr == 'l'){
                        gpio_set_level(O_LR,0);
                        ESP_LOGI(TAG,"LED RELAY IS OFF");
                }
                else if(chr == 'N'){
                        gpio_set_level(O_EX,1) ;                                 
                        }
                else if(chr == 'n'){
                        gpio_set_level(O_EX,0);
                        ESP_LOGI(TAG,"EXTRA RELAY IS OFF");
                }
                else if(chr == 'E'){
                        gpio_set_level(EMR_SAF,1);
                        ESP_LOGI(TAG,"Safmet in EMR is ON");
                }
                else if(chr == 'e'){
                        gpio_set_level(EMR_SAF,0);
                        ESP_LOGI(TAG,"Safmet in EMR is OFF");
                }
                else if(chr == 'A'){
                        gpio_set_level(ALR_SAF,1);
                        ESP_LOGI(TAG,"Safmet in ALR is ON");
                }
                else if(chr == 'a'){
                        gpio_set_level(ALR_SAF,0);
                        ESP_LOGI(TAG,"Safmet in ALR is OFF");
                }
                else if(chr == 'C'){
                        gpio_set_level(N_RE,1);
                        ESP_LOGI(TAG,"NODE RELAY IS ON");
                }
                else if(chr == 'c'){
                        gpio_set_level(N_RE,0);
                        ESP_LOGI(TAG,"NODE RELAY IS OFF");
                }
        }
}


void opt_input(){
        while(1){
	     int  curr_rev = gpio_get_level(REV);
             int curr_aux =gpio_get_level(AUX);
              int curr_frk_det=gpio_get_level(FRK_DET);
             int  curr_i_sb=gpio_get_level(I_SB);

        if(curr_rev != prev_rev){
	      ESP_LOGI(TAG, "Input pin %d is %s",REV, curr_rev? "high" : "low");
	      prev_rev = curr_rev;
	}
        if(curr_aux != prev_aux){
        ESP_LOGI(TAG, "Input pin %d is %s", AUX,curr_aux?  "high" : "low");
        prev_aux= curr_aux;
        }
        if(curr_frk_det!= prev_frk_det){
        ESP_LOGI(TAG, "Input pin %d is %s", FRK_DET, curr_frk_det? "high" : "low");
        prev_frk_det = curr_frk_det;
        }
        if(curr_i_sb!= prev_i_sb){
        ESP_LOGI(TAG, "Input pin %d is %s", I_SB, curr_i_sb? "high" : "low");
        prev_i_sb = curr_i_sb;
        }
  vTaskDelay(100/portTICK_PERIOD_MS);
	}
vTaskDelete(NULL);
} 


void app_main(void)
{

    /* Configure the peripheral according to the LED type */
    configure_gpio_output(EMR_SAF);
    configure_gpio_output(ALR_SAF);
    configure_gpio_output(O_TR);
    configure_gpio_output(O_FR);
    configure_gpio_output(O_LR);
    configure_gpio_output(O_EX);
    configure_gpio_output(N_RE);
    configure_gpio_input(REV);
    configure_gpio_input(AUX);
    configure_gpio_input(FRK_DET);
    configure_gpio_input(I_SB);


    while(1) {
        relay_ctrl();
         xTaskCreate(opt_input, "INPUT", 2048, NULL, 10, NULL);
        vTaskDelay(100/portTICK_PERIOD_MS);
     }
}
