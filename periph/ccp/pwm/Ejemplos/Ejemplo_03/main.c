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

/* Declaración de funciones */
void CCP1_PWM_Inicializar(void);

/* Función principal */
int main(void){
    
    int8_t ciclo_trabajo = 0;
    
    /* Configurar el PUERTO D como salida */
    TRISD = 0x00;
    /* Configurar el módulo CCP1 en modo PWM */
    CCP1_PWM_Inicializar();
    
    while(1)
    {
        /* Incrementar el ciclo de trabajo de 1% a 99% en dos segundos (aprox) */
        for(ciclo_trabajo = 1; ciclo_trabajo <= 99; ciclo_trabajo++)
        {
            CCP1_PWM_Set_Duty_Cycle((uint8_t)ciclo_trabajo);
            __delay_ms(20);
        }
        
        /* Decrementar el ciclo de trabajo de 99% a 1% en dos segundos (aprox) */
        for(ciclo_trabajo = 99; ciclo_trabajo >= 1; ciclo_trabajo--)
        {
            CCP1_PWM_Set_Duty_Cycle((uint8_t)ciclo_trabajo);
            __delay_ms(20);
        }        

    }
    
    return 0;
}


/* Definición de funciones */


/* Configurar una señal PWM 1, de 10 KHz y ciclo de trabajo 1% aproximadamente */

void CCP1_PWM_Inicializar(void)
{
    ccp_pwm_t my_pwm;
    
    my_pwm.timer2_prescaler = TIMER2_PRESCALER_4;
    my_pwm.timer2_top_value = 124;
    my_pwm.duty_cycle = 20;
    
    CCP1_PWM_Configure(&my_pwm);
}

