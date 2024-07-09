#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "freertos/timers.h"

#define btt 17
#define LED 2

void app_main() {
     
    gpio_reset_pin(LED); 
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    gpio_set_direction(btt, GPIO_MODE_INPUT);
    gpio_set_pull_mode(btt,GPIO_PULLDOWN_ONLY);
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
            
            vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}