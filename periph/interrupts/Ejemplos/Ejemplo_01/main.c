/*
 * File:   main.c
 * Author: mtorres
 *
 * Created on 24 de septiembre de 2022, 11:51 AM
 */

/* Inclusión de archivos */
#include "system_config.h"
#include <xc.h>
#include "MT_timer.h"


/* Definición de macros */

/* Definición de variables */

/* Declaración de funciones */
void Timer0_Inicializar(void);

/* Función principal */
int main(void){
    
    /* Configurar RD0 somo salida */
    TRISDbits.RD0 = 0;
    /* COnfigurar el Timer0 */
    Timer0_Inicializar();
    /* Habilitar las interrupciones */
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    RCONbits.IPEN = 0;
    
    while(1)
    {

    }
    
    return 0;
}

/* Rutina de servicio a interrupciones (ISR) */
__interrupt() void ISR(void)
{
    Timer0_Reload();
    LATDbits.LATD0 = !LATDbits.LATD0;
}


/* Definición de funciones */

/* El Timer0 interrumpe cada 1 segundo */

void Timer0_Inicializar(void)
{
    timer0_t my_timer;
    
    my_timer.timer_status = TIMER0_ON;
    my_timer.clock_source = TIMER0_INTERNAL_CLOCK;
    my_timer.ext_clock_edge = TIMER0_EXT_CLK_RISING_EDGE;
    my_timer.timer_bits = TIMER0_16_BITS;
    my_timer.prescaler = TIMER0_PRESCALER_128;
    my_timer.offset = 26473;
    my_timer.overflow_interrupt = TIMER0_INTERRUPT_ENABLED;
    
    Timer0_Configure(&my_timer);
}