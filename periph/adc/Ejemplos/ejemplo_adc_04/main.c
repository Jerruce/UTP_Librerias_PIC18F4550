/*
 * File:   main.c
 * Author: mtorres
 *
 * Created on 24 de septiembre de 2022, 11:51 AM
 */

/* Inclusión de archivos */
#include "system_config.h"
#include <xc.h>
#include <stdint.h>
#include "MT_ccp.h"
#include "MT_timer.h"
#include "MT_adc.h"

/* Definición de variables */
volatile uint8_t leer_potenciometro = 0;

/* Declaración de funciones */
void Timer0_Inicializar(void);
void ADC_Inicializar(void);
void CCP1_PWM_Inicializar(void);

/* Función principal */
int main(void){
    
    uint16_t valor_adc = 0;
    uint32_t ciclo_trabajo = 0;
    
    /* Configurar el PUERTO D como salida */
    TRISD = 0x00;
    /* Configurar los módulos */
    CCP1_PWM_Inicializar();
    ADC_Inicializar();
    ADC_Channel_Select(ADC_CHANNEL_0);
    Timer0_Inicializar();
     /* Habilitar las interrupciones */
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    RCONbits.IPEN = 0;   
    
    while(1)
    {
        /* Leer el potenciómetro cada 10ms */
        if(leer_potenciometro == 1)
        {
            /* Limmpiar la bandera */
            INTCONbits.GIE = 0;
            leer_potenciometro = 0;
            INTCONbits.GIE = 1;
            /* Iniciar conversión */
            ADC_Start_Conversion();
            while(ADC_Check_Conversion_Status() == 1)
            {
                /* Esperar hasta que la conversión se complete */
            }
            /* Aplicar un ciclo de trabajo proporcional al valor del ADC */
            valor_adc = ADC_Read_8_Bits();
            ciclo_trabajo = ((uint32_t)valor_adc * 100) / 255;
            CCP1_PWM_Set_Duty_Cycle((uint8_t)ciclo_trabajo);
        }
      
    }
    
    return 0;
}


/* Rutina de servicio a interrupciones (ISR) */
/* El Timer0 interrumpe cada 10ms */
__interrupt() void ISR(void)
{
    Timer0_Reload();
    leer_potenciometro = 1;
}


/* Definición de funciones */

/* Configurar el Timer0 para interrumpir cada 10ms */
void Timer0_Inicializar(void)
{
    timer0_t my_timer;
    
    my_timer.timer_status = TIMER0_ON;
    my_timer.clock_source = TIMER0_INTERNAL_CLOCK;
    my_timer.ext_clock_edge = TIMER0_EXT_CLK_RISING_EDGE;
    my_timer.timer_bits = TIMER0_16_BITS;
    my_timer.prescaler = TIMER0_PRESCALER_16;
    my_timer.offset = 62411;
    my_timer.overflow_interrupt = TIMER0_INTERRUPT_ENABLED;
    
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

/* Configurar una señal PWM 1, de 10 KHz y ciclo de trabajo 1% aproximadamente */

void CCP1_PWM_Inicializar(void)
{
    ccp_pwm_t my_pwm;
    
    my_pwm.timer2_prescaler = TIMER2_PRESCALER_4;
    my_pwm.timer2_top_value = 124;
    my_pwm.duty_cycle = 50;
    
    CCP1_PWM_Configure(&my_pwm);
}

