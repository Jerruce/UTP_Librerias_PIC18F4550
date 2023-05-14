/* 
 * File:   MT_ccp.h
 * Author: mtorres
 *
 * Created on 11 de octubre de 2022, 10:37 AM
 */

#ifndef MT_CCP_H
#define	MT_CCP_H


/* Inclusión de archivos */
#include <xc.h>
#include "MT_timer.h"

/* Definición de tipos */

typedef struct
{
    timer2_prescaler_t timer2_prescaler;
    uint8_t timer2_top_value;
    uint8_t duty_cycle;
}
ccp_pwm_t;


/* Declaración de funciones */
void CCP1_PWM_Configure(ccp_pwm_t *pwm_param);
void CCP2_PWM_Configure(ccp_pwm_t *pwm_param);
void CCP1_PWM_Set_Duty_Cycle(uint8_t percent);
void CCP2_PWM_Set_Duty_Cycle(uint8_t percent);

#endif	/* MT_CCP_H */

