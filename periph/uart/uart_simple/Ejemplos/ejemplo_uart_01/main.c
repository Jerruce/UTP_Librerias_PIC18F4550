/*
 * File:   main.c
 * Author: mtorres
 *
 * Created on 24 de septiembre de 2022, 08:31 AM
 */

/* Inclusión de archivos */
#include <xc.h>
#include "system_config.h"
#include "MT_uart.h"

void UART_Inicializar(void);


int main(void) 
{
 
    UART_Inicializar();
    
    while(1)
    {
       UARTn_Tx_String(UART0, "Prueba UART.\n\r");
        __delay_ms(1000);
    }
    
    return 0;
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