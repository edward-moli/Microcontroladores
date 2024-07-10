#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "driver/adc.h"

adc1_channel_t pot= ADC1_CHANNEL_1;

void config(void);


void app_main() 
{
    config();
    while (1)
    {
        int  pot2= adc1_get_raw(pot);
        printf("ADC: %d\n",pot);
        vTaskDelay(200/ portTICK_PERIOD_MS);

    }
    

}


void config(void)
{
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(pot,ADC_ATTEN_DB_11);

}