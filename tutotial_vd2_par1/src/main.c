#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "freertos/timers.h"

#define btt 17
#define LED 2
void confi (void);
void app_main() {
     confi();
   
    while (1) {
      
        int state=  gpio_get_level(btt);
        if (state)
        {
            gpio_set_level(LED, 1);
        }
        else
        {
            gpio_set_level(LED, 0);
        } 
            
            vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

void confi (void){
  gpio_config_t config;

    config.mode= GPIO_MODE_INPUT;
    config.pin_bit_mask=(1<<btt);
   config.pull_down_en=GPIO_PULLDOWN_ENABLE;
    config.pull_up_en=GPIO_PULLUP_DISABLE;
    config.intr_type=GPIO_INTR_DISABLE;
    gpio_config(&config);

    config.mode= GPIO_MODE_OUTPUT;
    config.pin_bit_mask=(1<<LED);
   config.pull_down_en=GPIO_PULLDOWN_ENABLE;
    config.pull_up_en=GPIO_PULLUP_DISABLE;
    config.intr_type=GPIO_INTR_DISABLE;
    gpio_config(&config);

}