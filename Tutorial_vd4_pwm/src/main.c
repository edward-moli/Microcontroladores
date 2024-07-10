#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/adc.h>
#include <driver/ledc.h>

adc1_channel_t pot = ADC1_CHANNEL_1;

#define LED 2
ledc_channel_config_t pwm;
void config(void);

void app_main() 
{
    config();
    while (1)
    {
        int pot2 = adc1_get_raw(pot);
        printf("ADC: %d\n", pot2);
        ledc_set_duty(pwm.speed_mode, pwm.channel, pot2);
        ledc_update_duty(pwm.speed_mode, pwm.channel);
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

void config(void)
{
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(pot, ADC_ATTEN_DB_11);
    
    ledc_timer_config_t timer = {
        .duty_resolution = LEDC_TIMER_12_BIT,
        .freq_hz = 1000,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ledc_timer_config(&timer);

    pwm.channel = LEDC_CHANNEL_0;
    pwm.duty = 0;
    pwm.gpio_num = LED;
    pwm.timer_sel = LEDC_TIMER_0;
    pwm.speed_mode = LEDC_LOW_SPEED_MODE;
    ledc_channel_config(&pwm);
}
