#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/timer.h>
#include <driver/gpio.h>

#define TRUE 1
#define falso 0
#define on 1
#define of 0
#define ESTADO_INIT 0
#define ESTADO_ABRIENDO 1
#define ESTADO_CERRANDO 2
#define ESTADO_CERRADO  3
#define ESTADO_ABIERTO 4
#define ESTADO_EMERGENCIA 5
#define ESTADO_ERROR 6
#define ESTADO_ESPERA 7
// configuracion de los pines a usar del sp
#define PIN_LSA  12  
#define PIN_LSC  14  
#define PIN_CA   27  
#define PIN_CC   26  
#define PIN_FC   25  
#define PIN_MC   33  
#define PIN_MA   32  
#define PIN_LED_EMER  23  
#define PIN_LED_MOV   22  


int FUNC_ESTADO_INIT ();
int FUNC_ESTADO_ABRIENDO ();
int FUNC_ESTADO_CERRANDO ();
int FUNC_ESTADO_CERRADO  ();
int FUNC_ESTADO_ABIERTO ();
int FUNC_ESTADO_EMERGENCIA(); 
int FUNC_ESTADO_ERROR ();
int FUNC_ESTADO_ESPERA();

volatile int ESTADO_ACTUAL = ESTADO_INIT;
volatile int ESTADO_SIGUIENTE = ESTADO_INIT;
volatile int ESTADO_ANTERIOR = ESTADO_INIT;
volatile unsigned int TimeCa = 0;

volatile struct INPUTS
{
    unsigned int LSA:1;
    unsigned int LSC:1;
    unsigned int CA:1;//comando abre
    unsigned int CC:1;//comando cierra
    unsigned int FC:1;
}INPUTS;

volatile struct OUTPUTS
{
    unsigned int MC:1;// MOTOR CERRANDO
    unsigned int MA:1;//MOTOR ABRIENDO
    unsigned int LED_EMER:1;
    unsigned int LED_MOV:1;
} outputs;

void app_main() {

    for(;;)
    {
        int LSA= gpio_get_level(PIN_LSA);

        if (ESTADO_SIGUIENTE==ESTADO_INIT)
        {
            ESTADO_SIGUIENTE=FUNC_ESTADO_INIT;
        }

         if (ESTADO_SIGUIENTE==ESTADO_ESPERA)
        {
            ESTADO_SIGUIENTE=FUNC_ESTADO_ESPERA;
        }
        
         if (ESTADO_SIGUIENTE==ESTADO_ABIERTO)
        {
            ESTADO_SIGUIENTE=FUNC_ESTADO_ABIERTO;
        }

         if (ESTADO_SIGUIENTE==ESTADO_CERRADO)
        {
            ESTADO_SIGUIENTE=FUNC_ESTADO_CERRADO;
        }

         if (ESTADO_SIGUIENTE==ESTADO_ABRIENDO)
        {
            ESTADO_SIGUIENTE=FUNC_ESTADO_ABRIENDO;
        }

         if (ESTADO_SIGUIENTE==ESTADO_CERRANDO)
        {
            ESTADO_SIGUIENTE=FUNC_ESTADO_CERRANDO;
        }

         if (ESTADO_SIGUIENTE==ESTADO_ERROR)
        {
            ESTADO_SIGUIENTE=FUNC_ESTADO_ERROR;
        }

         if (ESTADO_SIGUIENTE==ESTADO_EMERGENCIA)
        {
            ESTADO_SIGUIENTE=FUNC_ESTADO_EMERGENCIA;
        }

        
    }
}

int FUNC_ESTADO_INIT ()
{ while (1)
{
    return ESTADO_ESPERA;
}


}

int FUNC_ESTADO_ABRIENDO ()
{
     ESTADO_ANTERIOR= ESTADO_ACTUAL;
     ESTADO_ACTUAL = ESTADO_ESPERA;
    outputs.LED_EMER=of;
    outputs.LED_MOV=on;
    outputs.MA=TRUE;
    outputs.MC=falso;
    while (1)
{
    if (INPUTS.LSC==TRUE)
    {
        return ESTADO_CERRANDO;
    }
    
    if (INPUTS.FC==TRUE)
    {
       return ESTADO_EMERGENCIA;
    }
    if (INPUTS.LSA==TRUE && INPUTS.LSC==TRUE)
    {
        return ESTADO_ERROR;
    }
    if ( INPUTS.LSA== TRUE)
    {
        return ESTADO_ABIERTO;
    }
    
}

}
int FUNC_ESTADO_CERRANDO ()

{
     ESTADO_ANTERIOR= ESTADO_ACTUAL;
     ESTADO_ACTUAL = ESTADO_ESPERA;
    outputs.LED_EMER=of;
    outputs.LED_MOV=on;
    outputs.MA=falso;
    // poner tiempo de espera 10ms a 25ms, para que se active el relay o se apague
    outputs.MC=TRUE;

    while (1)
{
    if (INPUTS.LSC==TRUE)
    {
        return ESTADO_CERRADO;
    }
    //verificar fc y salida de emergencia
    // verificar el tiempo contador
    // verificar cambio de giro
    
    if (INPUTS.FC==true)
    {
        return ESTADO_EMERGENCIA;
    }
    
    if (INPUTS.LSC==true && INPUTS.LSA)
    {
        return ESTADO_ERROR;
    }
    // if ( )retorno para error en un tiempo de 3
    
    
    
}

}

int FUNC_ESTADO_CERRADO  ()
{
    ESTADO_ANTERIOR= ESTADO_ACTUAL;
    ESTADO_ACTUAL = ESTADO_ESPERA;
    outputs.LED_EMER=of;
    outputs.LED_MOV=of;
    outputs.MA=falso;
    outputs.MC=falso;
    //esperamos que el motor se detenga
    while (1)
{
    return ESTADO_ESPERA;
}

}

int FUNC_ESTADO_ABIERTO ()
{
    ESTADO_ANTERIOR= ESTADO_ACTUAL;
    ESTADO_ACTUAL = ESTADO_ESPERA;
    outputs.LED_EMER=of;
    outputs.LED_MOV=of;
    outputs.MA=falso;
    outputs.MC=falso;
    //PONER UN tiempo
    while (1)
    {
       return ESTADO_ESPERA;
        
    }
}
int FUNC_ESTADO_EMERGENCIA()
{
    while (1)
{
    
}
}
int FUNC_ESTADO_ERROR ()
{
    ESTADO_ANTERIOR= ESTADO_ACTUAL;
    ESTADO_ACTUAL = ESTADO_ESPERA;
    outputs.LED_EMER=of;
    outputs.LED_MOV=of;
    outputs.MA=of;
    outputs.MC=of;
while (1)
{
    
}
}
int FUNC_ESTADO_ESPERA()
{
    ESTADO_ANTERIOR= ESTADO_ACTUAL;
    ESTADO_ACTUAL = ESTADO_ESPERA;
    outputs.LED_EMER=of;
    outputs.LED_MOV=of;
    outputs.MA=of;
    outputs.MC=of;
while (1)
{
   
    if (INPUTS.LSC== falso && INPUTS.LSA==falso && INPUTS.FC==falso)
    {
        return(ESTADO_CERRANDO);
    }

    if (INPUTS.CA==TRUE && INPUTS.FC==falso && INPUTS.LSA==falso)
    {
        return ESTADO_ABRIENDO;
    }
    
    
}
}


