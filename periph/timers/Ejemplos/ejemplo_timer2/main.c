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

/* Declaración de funciones */
void Timer2_Inicializar(void);

/* Función principal */
int main(void){
    /* Configurar el PUERTO D como salida */
    TRISD = 0x00;
    /* Configurar el Timer2 */
    Timer2_Inicializar();
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
    /* Si la interrupción fue causada por el Timer2 */
    if(PIR1bits.TMR2IF == 1)
    {
        /* Limpiar la bandera */
        PIR1bits.TMR2IF = 0;
        /* Conmutar el pin RD0 */
        LATDbits.LATD0 = !LATDbits.LATD0;
    }
}

/* Definición de funciones */

/* Configurar el Timer2 para interrumpir cada 1ms (aproximadamente)*/
void Timer2_Inicializar(void)
{
    timer2_t my_timer;
    
    my_timer.timer_status = TIMER2_ON;
    my_timer.prescaler = TIMER2_PRESCALER_16;
    my_timer.top_value = 77;
    my_timer.postscaler = TIMER2_POSTSCALER_4;
    my_timer.match_interrupt = TIMER2_INTERRUPT_ENABLED;
    
    Timer2_Configure(&my_timer);
}



