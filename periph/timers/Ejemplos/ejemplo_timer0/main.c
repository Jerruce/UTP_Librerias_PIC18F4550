/*
 * File:   main.c
 * Author: mtorres
 *
 * Created on 24 de septiembre de 2022, 08:31 AM
 */

/* Inclusión de archivos */
#include <xc.h>
#include "system_config.h"
#include "MT_timer.h"


void Timer0_Inicializar(void);

int main(void) 
{
 
    TRISDbits.TRISD0 = 0;
    Timer0_Inicializar();
           
    while(1)
    {
        /* Conmutar el LED cada vez que el Timer0 se desborde*/
        if(INTCONbits.TMR0IF == 1)
        {
            Timer0_Reload();
            PORTDbits.RD0 = !PORTDbits.RD0;
        }
        
    }
    
    return 0;
}


void Timer0_Inicializar(void)
{
    timer0_t my_timer;
    
    my_timer.timer_status = TIMER0_ON;
    my_timer.clock_source = TIMER0_INTERNAL_CLOCK;
    my_timer.ext_clock_edge = TIMER0_EXT_CLK_RISING_EDGE;
    my_timer.timer_bits = TIMER0_16_BITS;
    my_timer.prescaler = TIMER0_PRESCALER_256;
    my_timer.offset = 46005;
    my_timer.overflow_interrupt = TIMER0_INTERRUPT_DISABLED;
    
    Timer0_Configure(&my_timer);
}