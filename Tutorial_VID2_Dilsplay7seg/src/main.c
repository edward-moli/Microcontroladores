#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include "freertos/task.h"

#define btt 48

int DIS[7] = {5, 6, 7, 3, 36, 37, 39};

char number[10][7] = {
    {0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 1},
    {0, 0, 1, 0, 0, 1, 0},
    {0, 0, 0, 0, 1, 1, 0},
    {1, 0, 0, 1, 1, 0, 0},
    {0, 1, 0, 0, 1, 0, 0},
    {0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0},
};

void confi(void);

void app_main() {
    confi();
    int cnt = 0;

    for (int i = 0; i < 7; i++) {
        gpio_set_level(DIS[i], number[0][i]);
    }

    while (1) {
        int state = gpio_get_level(btt);
        for (int i = 0; i < 7; i++) {
            gpio_set_level(DIS[i], number[cnt][i]);
        }
        
        if (state == 1) {
            cnt = (cnt + 1) % 10;
        }

        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

void confi(void) {
    gpio_config_t config;

    config.mode = GPIO_MODE_INPUT;
    config.pin_bit_mask = (1ULL << btt);
    config.pull_down_en = GPIO_PULLDOWN_ENABLE;
    config.pull_up_en = GPIO_PULLUP_DISABLE;
    config.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&config);

    config.mode = GPIO_MODE_OUTPUT;
    config.pin_bit_mask = (1ULL << DIS[0]) |
                          (1ULL << DIS[1]) |
                          (1ULL << DIS[2]) |
                          (1ULL << DIS[3]) |
                          (1ULL << DIS[4]) |
                          (1ULL << DIS[5]) |
                          (1ULL << DIS[6]);
    config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    config.pull_up_en = GPIO_PULLUP_DISABLE;
    config.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&config);
}
