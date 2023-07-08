
/* Inclusión de archivos */
#include "MT_timer.h"

volatile uint16_t timer0_offset = 0;

/* Definición de funciones */
void Timer0_Configure(timer0_t *timer_param)
{
    
    /* Inicializar registro */
    T0CON = 0;
    
    /* PASO 1: Desactivar el Timer0 */
    T0CONbits.TMR0ON = 0;

    /* PASO 2: Configurar el Timer0 en modo 8 bits o 16 bits */
    if(timer_param->timer_bits == TIMER0_16_BITS)
    {
        T0CONbits.T08BIT = 0;    
    }
    else
    {
        T0CONbits.T08BIT = 1;
    }
    
    /* PASO 3: Configurar la fuente de reloj (interna o externa) */
    if(timer_param->clock_source == TIMER0_EXTERNAL_CLOCK)
    {
        T0CONbits.T0CS = 1;    
    }
    else
    {
        T0CONbits.T0CS = 0;    
    }
    
    /*PASO 4: Configurar el flanco de activación del clock externo */
    if(timer_param->ext_clock_edge == TIMER0_EXT_CLK_FALLING_EDGE)
    {
        T0CONbits.T0SE = 1;
    }
    else
    {
        T0CONbits.T0SE = 0;
    }
    
    /* PASO 5: Habilitar y configurar el Pre-Scaler */
    if(timer_param->prescaler == TIMER0_PRESCALER_1)
    {
        T0CONbits.PSA = 1; // Prescaler desactivado
    }
    else
    {
        T0CONbits.PSA = 0; // Prescaler activado
        T0CON |= timer_param->prescaler & 0b00000111;
    }
        
    /* PASO 6: Limpiar la bandera y cargar el valor OFFSET */
    timer0_offset = timer_param->offset;
    Timer0_Reload();
    
    /* PASO 7: Activar el Timer0 de ser el caso */
    if(timer_param->timer_status == TIMER0_ON)
    {
        T0CONbits.TMR0ON = 1;    
    }
    else
    {
        T0CONbits.TMR0ON = 0;
    }
    
    /* PASO 8: Activar la interrupción por desbordamiento,
      de ser el caso */
    if(timer_param->overflow_interrupt == TIMER0_INTERRUPT_ENABLED)
    {
        INTCONbits.TMR0IE = 1;
    }
    else
    {
        INTCONbits.TMR0IE = 0;
    }
   
}


void Timer0_Reload(void)
{
    /* PASO 1: Limpiar la bandera de desbordamiento del Timer0 */
    INTCONbits.TMR0IF = 0;
    /* PASO 2: Cargar el valor OFFSET en el Timer0 */    
    TMR0H = (timer0_offset >> 8) & 0x00FF;
    TMR0L = timer0_offset & 0x00FF;
}


void Timer2_Configure(timer2_t *timer_param)
{
    /* Inicializar registro */
    T2CON = 0;
    
    /* PASO 1: Desactivar el Timer2 */
    T2CONbits.TMR2ON = 0; 
    /* PASO 2: Configurar el pre-scaler */
    T2CONbits.T2CKPS = (timer_param->prescaler) & 0x03;
    /* PASO 3: Configurar el post-scaler */
    T2CONbits.TOUTPS = (timer_param->postscaler) & 0x0F;
    /* PASO 4: Configurar el valor TOP */
    PR2 = timer_param->top_value;
    /* PASO 5: Activar el Timer2 de ser el caso */
    if(timer_param->timer_status == TIMER2_ON)
    {
        T2CONbits.TMR2ON = 1;    
    }
    else
    {
        T2CONbits.TMR2ON = 0;
    }
    /* PASO 6: Activar la interrupción, de ser el caso */
    if(timer_param->match_interrupt == TIMER2_INTERRUPT_ENABLED)
    {
        PIE1bits.TMR2IE = 1;
    }
    else
    {
        PIE1bits.TMR2IE = 0;
    }
    
}