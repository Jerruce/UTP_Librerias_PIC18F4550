/*
 * File:   main.c
 * Author: mtorres
 *
 * Created on 8 de julio de 2023, 03:40 PM
 */

/* Inclusión de archivos */
#include "system_config.h"
#include <xc.h>
#include "MT_timer.h"
#include "MT_uart_buffered.h"

/* Definición de macros */
#define TX_BUFF_SIZE    100
#define RX_BUFF_SIZE    10

/* Arreglos donde se almacenan los bytes enviados y recibidos por el UART */
volatile char tx_buffer[TX_BUFF_SIZE];
volatile char rx_buffer[RX_BUFF_SIZE];

bool hora_de_imprimir = false; // Bandera que indica que se debe imprimir 


/* Declaración de funciones */
void Timer0_Inicializar(void);
void UART_Initializar(void);


/* FUnción principal */
int main(void) {
    
    /* Configurar el Timer 0 para interrumpir cada 1 segundo*/
    Timer0_Inicializar();
    
    /* COnfigurar el UART */
    UART_Initializar();
    
    /* Habilitar las interrupciones */
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    RCONbits.IPEN = 0;
    
    /* Repetir indefinidamente ...*/
    while(1)
    {
        if(hora_de_imprimir)
        {
             INTCONbits.GIE = 0;
             hora_de_imprimir = false;
             INTCONbits.GIE = 1;
             UARTn_Tx_String(UART0, "Hola mundo.\n\r");
        }
    }
    
    return 0;
}


/* Rutina de servicio a interrupciones (ISR) */
__interrupt() void ISR(void)
{
    if(INTCONbits.TMR0IF == 1)
    {
        Timer0_Reload();
        hora_de_imprimir = true;
        INTCONbits.TMR0IF = 0;
    }

    
    if(PIR1bits.TXIF == 1)
    {
        UART0_Tx_ISR_Callback();
        PIR1bits.TXIF = 0;
    }
    
}


/* Definición de funciones */

void Timer0_Inicializar(void)
{
    timer0_t my_timer;
    
    my_timer.timer_status = TIMER0_ON;
    my_timer.clock_source = TIMER0_INTERNAL_CLOCK;
    my_timer.ext_clock_edge = TIMER0_EXT_CLK_RISING_EDGE;
    my_timer.timer_bits = TIMER0_16_BITS;
    my_timer.prescaler = TIMER0_PRESCALER_128;
    my_timer.offset = 26473;
    my_timer.overflow_interrupt = TIMER0_INTERRUPT_ENABLED;
    
    Timer0_Configure(&my_timer);
}

void UART_Initializar(void)
{
    uart_t my_uart;
    
    my_uart.baud_rate = BAUD_9600_BPS;
    my_uart.data_bits = UART_8_DATA_BITS;
    my_uart.tx_status = UART_TX_ENABLED;
    my_uart.rx_status = UART_RX_DISABLED;
    my_uart.rx_interrupt = UART_RX_INTERRUPT_DISABLED;
    my_uart.tx_interrupt = UART_TX_INTERRUPT_ENABLED;
    my_uart.tx_buffer_ptr = tx_buffer;
	my_uart.tx_buffer_size = TX_BUFF_SIZE;
	my_uart.rx_buffer_ptr = rx_buffer;
	my_uart.rx_buffer_size = RX_BUFF_SIZE;
    
    UART0_Configure(&my_uart);
}