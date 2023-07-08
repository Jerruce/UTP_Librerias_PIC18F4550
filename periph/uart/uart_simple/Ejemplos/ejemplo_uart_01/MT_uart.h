/* 
 * File:   MT_uart.h
 * Author: mtorres
 *
 * Created on 24 de septiembre de 2022, 08:35 AM
 */

#ifndef MT_UART_H
#define	MT_UART_H

/* Inclusión de archivos */
#include <xc.h>
#include <stdint.h>

/* Definición de macros */
#define F_OSC              20000000UL

/* Definición de tipos */
typedef enum
{
	UART0 = 0,
	UART1,
	UART2,
	UART3
}
uart_module_t;


typedef enum
{
    UART_8_DATA_BITS = 0,
    UART_9_DATA_BITS
}
uart_data_bits_t;

typedef enum
{
	UART_TX_DISABLED = 0,
	UART_TX_ENABLED
}
uart_tx_status_t;

typedef enum
{
	UART_RX_DISABLED = 0,
	UART_RX_ENABLED
}
uart_rx_status_t;


typedef enum{
	BAUD_300_BPS = 300,
	BAUD_600_BPS = 600,
	BAUD_1200_BPS = 1200,
	BAUD_2400_BPS = 2400,
	BAUD_4800_BPS = 4800,
	BAUD_9600_BPS = 9600,
	BAUD_19200_BPS = 19200,
	BAUD_38400_BPS = 38400,
	BAUD_57600_BPS = 57600,
	BAUD_115200_BPS = 115200
}
uart_baud_rate_t;


typedef enum
{
    UART_RX_INTERRUPT_DISABLED = 0,
    UART_RX_INTERRUPT_ENABLED
}
uart_rx_interrupt_status_t;

typedef enum
{
    UART_TX_INTERRUPT_DISABLED = 0,
    UART_TX_INTERRUPT_ENABLED
}
uart_tx_interrupt_status_t;


typedef struct
{
    uart_data_bits_t data_bits;
    uart_tx_status_t tx_status;
    uart_rx_status_t rx_status;
    uart_baud_rate_t baud_rate;
    uart_tx_interrupt_status_t tx_interrupt;
    uart_rx_interrupt_status_t rx_interrupt;
}
uart_t;

/* Declaración de funciones */
void UART0_Configure(uart_t *uart_param);
void UARTn_Tx_Byte(uart_module_t uart_n, char byte);
void UARTn_Tx_String(uart_module_t uart_n, char str[]);
void UARTn_Tx_Integer(uart_module_t uart_n, int32_t num);

#endif	/* MT_UART_H */

