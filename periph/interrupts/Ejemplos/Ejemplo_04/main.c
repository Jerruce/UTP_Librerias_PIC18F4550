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
#include "MT_uart.h" 

/* Definición de macros */

/* Definición de variables */
volatile uint8_t imprimir_mensaje = 0;

/* Declaración de funciones */
void Timer0_Inicializar(void);
void UART_Inicializar(void);

/* Función principal */
int main(void){
    
    /* Configurar PUERTO D somo salida */
    TRISD = 0;
    /* COnfigurar el UART */
    UART_Inicializar();
    /* COnfigurar el Timer0 */
    Timer0_Inicializar();
    /* Habilitar las interrupciones */
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    RCONbits.IPEN = 0;
    
    while(1)
    {
        if(imprimir_mensaje == 1)
        {
            INTCONbits.GIE = 0;
            imprimir_mensaje = 0;
            INTCONbits.GIE = 1;
            
            UARTn_Tx_String(UART0, "Hola mundo\n\r.");
        }

    }
    
    return 0;
}

/* Rutina de servicio a interrupciones (ISR) */
__interrupt() void ISR(void)
{
    static uint16_t conta_led_1ms = 0;
    static uint16_t conta_uart_1ms = 0;
    
    Timer0_Reload();
    
    /* Conmutar el LED cada 500 ms*/
    conta_led_1ms++;
    if(conta_led_1ms >=  500)
    {
        conta_led_1ms = 0;
        LATDbits.LATD0 = !LATDbits.LATD0;
    }
    
    /* Imprimir por el UART cada 1 segundo */
    conta_uart_1ms++;
    if(conta_uart_1ms >= 1000)
    {
        conta_uart_1ms = 0;
        imprimir_mensaje = 1;
    }
}


/* Definición de funciones */

/* El Timer0 interrumpe cada 1ms */

void Timer0_Inicializar(void)
{
    timer0_t my_timer;
    
    my_timer.timer_status = TIMER0_ON;
    my_timer.clock_source = TIMER0_INTERNAL_CLOCK;
    my_timer.ext_clock_edge = TIMER0_EXT_CLK_RISING_EDGE;
    my_timer.timer_bits = TIMER0_16_BITS;
    my_timer.prescaler = TIMER0_PRESCALER_8;
    my_timer.offset = 64911;
    my_timer.overflow_interrupt = TIMER0_INTERRUPT_ENABLED;
    
    Timer0_Configure(&my_timer);
}


void UART_Inicializar(void)
{
    uart_t my_uart;
    
    my_uart.baud_rate = BAUD_9600_BPS;
    my_uart.data_bits = UART_8_DATA_BITS;
    my_uart.tx_status = UART_TX_ENABLED;
    my_uart.rx_status = UART_RX_DISABLED;
    my_uart.rx_interrupt = UART_RX_INTERRUPT_DISABLED;
    my_uart.tx_interrupt = UART_TX_INTERRUPT_DISABLED;
    
    UART0_Configure(&my_uart);
    
}
