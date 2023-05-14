/*
 * File:   main.c
 * Author: mtorres
 *
 * Created on 24 de septiembre de 2022, 11:51 AM
 */

/* Inclusión de archivos */
#include "system_config.h"
#include <xc.h>
#include "MT_ccp.h"

/* Declaración de funciones */
void CCP1_PWM_Inicializar(void);

/* Función principal */
int main(void){
    /* Configurar el PUERTO D como salida */
    TRISD = 0x00;
    /* Configurar el módulo CCP1 en modo PWM */
    CCP1_PWM_Inicializar();
    
    while(1)
    {

    }
    
    return 0;
}


/* Definición de funciones */


/* Configurar una señal PWM de 10 KHz y ciclo de trabajo 20% aproximadamente*/
void CCP1_PWM_Inicializar(void)
{
    ccp_pwm_t my_pwm;
    
    my_pwm.timer2_prescaler = TIMER2_PRESCALER_4;
    my_pwm.timer2_top_value = 124;
    my_pwm.duty_cycle = 20;
    
    CCP1_PWM_Configure(&my_pwm);
}

