#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "freertos/timers.h"

#define LED 2

void app_main() {
    gpio_reset_pin(LED); 
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
  

    while (1) {
      
        
            gpio_set_level(LED, 1);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            gpio_set_level(LED, 0);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}