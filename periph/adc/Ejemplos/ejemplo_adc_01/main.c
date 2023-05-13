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
#include "MT_adc.h"

/* Declaración de funciones */
void Timer0_Inicializar(void);
void ADC_Inicializar(void);

/* Función principal */
int main(void) 
{
    
    uint16_t valor_adc = 0;
    
    /* Configurar el PUERTO D como salida*/
    TRISD = 0x00;
    /* Inicializar el ADC y el Timer0 */
    ADC_Inicializar();
    ADC_Channel_Select(ADC_CHANNEL_0);
    Timer0_Inicializar();
        
    while(1)
    {
        /* Realizar conversión con el ADC y mostrar valor en 
         * los LEDs cada 10ms */
        if(INTCONbits.TMR0IF == 1)
        {
            Timer0_Reload();
            /* Iniciar conversión */
            ADC_Start_Conversion();
            while(ADC_Check_Conversion_Status() == 1)
            {
                /* Esperar hasta que la conversión se complete */
            }
            /* Mostrar el valor del ADC en los LEDs*/
            valor_adc = ADC_Read_10_Bits();
            LATD = (valor_adc >> 2);
            
        }
        
    }
    
    return 0;
}

/* Definición de funciones */

/* Configurar el Timer0 para contar 10ms */
void Timer0_Inicializar(void)
{
    timer0_t my_timer;
    
    my_timer.timer_status = TIMER0_ON;
    my_timer.clock_source = TIMER0_INTERNAL_CLOCK;
    my_timer.ext_clock_edge = TIMER0_EXT_CLK_RISING_EDGE;
    my_timer.timer_bits = TIMER0_16_BITS;
    my_timer.prescaler = TIMER0_PRESCALER_16;
    my_timer.offset = 62411;
    my_timer.overflow_interrupt = TIMER0_INTERRUPT_DISABLED;
    
    Timer0_Configure(&my_timer);
}


/* El ADC demora, aproximadamente,13us en realizar una conversión */
void ADC_Inicializar(void)
{
    adc_t my_adc;
    
    my_adc.pbaden_status = PBADEN_OFF;
    my_adc.adc_status = ADC_ENABLED;
    my_adc.data_format = ADC_RIGHT_JUSTIFIED;
    my_adc.channels_enabled = ADC_1_CHANNEL_ENABLED;
    my_adc.clock_source = ADC_CLK_FOSC_16;
    my_adc.acq_time = ADC_ACQ_TIME_4_TAD;
    my_adc.voltage_reference = ADC_VREF_VCC;
    my_adc.adc_interrupt = ADC_INTERRUPT_DISABLED;
   
    ADC_Configure(&my_adc);
}