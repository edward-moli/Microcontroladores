#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

// Definición de pines
#define LSC_PIN 5
#define LSA_PIN 35
#define FC_PIN 3 //SI FUNCIONA
#define CC_PIN 48
#define NFC_PIN 17 //SI FUNCIONA
#define CA_PIN 46 //SI FUNCIONA
//SALIDAS
#define LED_MOV_PIN 37 // FUNCIONA
#define LED_EMER_PIN 2 // FUNCIONA
#define MC_PIN 47 // FUNCIONA
#define MA_PIN 35 //FUNCIONA

// Variables globales para almacenar los niveles de los pines
int FC, LSC, LSA, CC, CA, NFC;
int EMER = 0; // Estado del LED de emergencia (0 = apagado, 1 = encendido)
void CONFig();
// Función para leer los niveles de los pines
void read_pin_levels() {
    FC = gpio_get_level(FC_PIN);
    LSC = gpio_get_level(LSC_PIN);
    LSA = gpio_get_level(LSA_PIN);
    CC = gpio_get_level(CC_PIN);
    CA = gpio_get_level(CA_PIN);
    NFC = gpio_get_level(NFC_PIN);
}

void app_main() {
    CONFig();

    while (1) {
        read_pin_levels();

        if (FC && !EMER) {
            // Si FC es presionado y el LED de emergencia está apagado
            EMER = 1; // Enclavar el LED de emergencia
            gpio_set_level(LED_EMER_PIN, 1);
            gpio_set_level(LED_MOV_PIN, 0);
            gpio_set_level(MA_PIN, 0); 
            gpio_set_level(MC_PIN, 0);
        } else if (NFC && EMER) {
            // Si NFC es presionado y el LED de emergencia está encendido
            EMER = 0; // Desenclavar el LED de emergencia
            gpio_set_level(LED_EMER_PIN, 0);
        }

        if (!EMER) {
            // Si el LED de emergencia está apagado, continuar con la lógica normal
            if (CA&&LSC) {
                gpio_set_level(LED_MOV_PIN, 1);
                gpio_set_level(MA_PIN, 1);
                gpio_set_level(MC_PIN, 0);
            } else if (CC&&LSA) {
                gpio_set_level(LED_MOV_PIN, 1);
                gpio_set_level(MA_PIN, 0);
                gpio_set_level(MC_PIN, 1);
            }
             else if (LSA&&!CC)
           {
            gpio_set_level(MA_PIN, 0);
            gpio_set_level(LED_MOV_PIN, 0);
            }
                else if (LSC&&!CA)
            {
            gpio_set_level(MA_PIN, 0);
            gpio_set_level(LED_MOV_PIN, 0);
            gpio_set_level(MC_PIN, 0);
            }
            
        }
        
         else 
         {
            // Si el LED de emergencia está encendido, ignorar CA y CC
            gpio_set_level(LED_MOV_PIN, 0);
            gpio_set_level(MA_PIN, 0);
            gpio_set_level(MC_PIN, 0);
        }
        if (LSA&&LSC)
        {
            printf("error");
            gpio_set_level(LED_MOV_PIN, 0);
            gpio_set_level(CC_PIN, 0);
            gpio_set_level(CC_PIN, 0);
        }
        
        
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void CONFig() {
    gpio_set_direction(FC_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(LSC_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(LSA_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(CC_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(CA_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(NFC_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(LED_EMER_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_MOV_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(MA_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(MC_PIN, GPIO_MODE_OUTPUT);
}
