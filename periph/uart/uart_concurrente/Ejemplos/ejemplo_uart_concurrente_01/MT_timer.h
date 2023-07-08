/* 
 * File:   MT_timer.h
 * Author: mtorres
 *
 * Created on 24 de septiembre de 2022, 10:27 AM
 */

#ifndef MT_TIMER_H
#define	MT_TIMER_H

/* Inclusión de archivos */
#include <xc.h>
#include <stdint.h>

/* Definición de tipos */

typedef enum
{
    TIMER0_OFF = 0,
    TIMER0_ON
}
timer0_status_t;

typedef enum
{
    TIMER0_16_BITS = 0,
    TIMER0_8_BITS        
}
timer0_bits_t;

typedef enum
{
    TIMER0_INTERNAL_CLOCK = 0,
    TIMER0_EXTERNAL_CLOCK
}
timer0_clock_source_t;

typedef enum
{
    TIMER0_EXT_CLK_RISING_EDGE = 0,
    TIMER0_EXT_CLK_FALLING_EDGE        
}
timer0_ext_clock_edge_t;

typedef enum
{
    TIMER0_INTERRUPT_DISABLED = 0,
    TIMER0_INTERRUPT_ENABLED        
}
timer0_interrupt_status_t;

typedef enum
{
    TIMER0_PRESCALER_2 = 0,
    TIMER0_PRESCALER_4,
    TIMER0_PRESCALER_8,
    TIMER0_PRESCALER_16,
    TIMER0_PRESCALER_32,
    TIMER0_PRESCALER_64,
    TIMER0_PRESCALER_128,
    TIMER0_PRESCALER_256,
    TIMER0_PRESCALER_1
}
timer0_prescaler_t;

typedef struct
{
    uint16_t offset;
    timer0_status_t timer_status;
    timer0_bits_t timer_bits;
    timer0_clock_source_t clock_source;
    timer0_ext_clock_edge_t ext_clock_edge;
    timer0_prescaler_t prescaler;
    timer0_interrupt_status_t overflow_interrupt;
}
timer0_t;


typedef enum
{
    TIMER2_OFF = 0,
    TIMER2_ON
}
timer2_status_t;


typedef enum
{
    TIMER2_POSTSCALER_1 = 0,    
    TIMER2_POSTSCALER_2,
    TIMER2_POSTSCALER_3,
    TIMER2_POSTSCALER_4,
    TIMER2_POSTSCALER_5,
    TIMER2_POSTSCALER_6,
    TIMER2_POSTSCALER_7,
    TIMER2_POSTSCALER_8,
    TIMER2_POSTSCALER_9,
    TIMER2_POSTSCALER_10,
    TIMER2_POSTSCALER_11,
    TIMER2_POSTSCALER_12,
    TIMER2_POSTSCALER_13,
    TIMER2_POSTSCALER_14,
    TIMER2_POSTSCALER_15,
    TIMER2_POSTSCALER_16         
}
timer2_postscaler_t;


typedef enum
{
    TIMER2_PRESCALER_1 = 0,
    TIMER2_PRESCALER_4,
    TIMER2_PRESCALER_16        
}
timer2_prescaler_t;


typedef enum
{
    TIMER2_INTERRUPT_DISABLED = 0,
    TIMER2_INTERRUPT_ENABLED        
}
timer2_interrupt_status_t;


typedef struct
{
    uint8_t top_value;
    timer2_status_t timer_status;
    timer2_prescaler_t prescaler;
    timer2_postscaler_t postscaler;
    timer2_interrupt_status_t match_interrupt;
}
timer2_t;


/* Declaración de funciones */
void Timer0_Configure(timer0_t *timer_param);
void Timer0_Reload(void);
void Timer2_Configure(timer2_t *timer_param);

#endif	/* MT_TIMER_H */

