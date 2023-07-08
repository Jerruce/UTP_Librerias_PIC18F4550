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
#include <stdbool.h>
#include "MT_serial_buffer.h"

/* Definición de macros */
#define F_OSC              20000000UL
#define UART_TX_BLOCK_MAX_SIZE_IN_BYTES      2000    


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
    
	char	*tx_buffer_ptr;	/**< Arreglo que almacena los bytes que se desea transmitir. */
	uint8_t	tx_buffer_size; /**< Tamaño del arreglo que almacena los bytes que se desea transmitir. */
	char	*rx_buffer_ptr;	/**< Arreglo que almacena los bytes que se reciben. */
	uint8_t rx_buffer_size;	/**< Tamaño del arreglo que almacena los bytes que se reciben. */    
}
uart_t;

/* Declaración de funciones */
void UART0_Configure(uart_t *uart_param);

/**
  * @brief Función para limpiar el buffer de transmisión de un UART.
  * @param uart_n Módulo UART correspondiente (UART0, UART1, UART2, UART3).
  * @details Ejemplo:
  * @code
    //Limpiar el buffer de transmisión del UART1
	UARTn_Tx_Buffer_Reset(UART1);
  * @endcode
  */
void UARTn_Tx_Buffer_Reset(uart_module_t uart_n);


/**
  * @brief Función para transmitir un byte por un módulo UART.
  * @param uart_n Módulo UART correspondiente (UART0, UART1, UART2, UART3).
  * @param byte Dato que se desea transmitir.
  * @return Si el byte se logró almacenar o no en el buffer de transmisión.
  * @details La función guarda un byte en el buffer de transmisión, siempre
  * y cuando éste cuente con espacio disponible. Si hay espacio en el buffer
  * y el byte se logra almacenar, la función retorna VERDADERO; de lo
  * contrario, si el buffer se encuentra lleno y el byte no se logra
  *	almacenar, la función retorna FALSO.\n  
  * Ejemplo:
  * @code
    //Transmitir el carácter 'A' por el UART0.
	UARTn_Tx_Byte(UART0, 'A');
  * @endcode
  */
bool UARTn_Tx_Byte(uart_module_t uart_n, char byte);

/**
  * @brief Función para transmitir un conjunto de bytes por un módulo UART.
  * @param uart_n Módulo UART correspondiente (UART0, UART1, UART2, UART3).
  * @param n_bytes Número de bytes que se desea transmitir.
  * @param data Arreglo que contiene los bytes que se desea transmisitr.
  * @return Si los bytes se lograron almacenar o no en el buffer de transmisión.
  * @details La función guarda los bytes en el buffer de transmisión, siempre 
  * y cuando éste cuente con espacio disponible. Si hay espacio en el buffer
  * y lo bytes se logran almacenar, la función retorna VERDADERO; de lo 
  * contrario, si el buffer se encuentra lleno y los bytes no se logran
  *	almacenar, la función retorna FALSO.\n
  * Ejemplo:
  * @code
    //Transmitir los bytes 0x03, 0x25 y 0x4C por el UART0.
    uint8_t arr[] = {0x03, 0x25, 0x4C}; 
    UARTn_Tx_Block(UART0, 3, arr);
  * @endcode
  */
bool UARTn_Tx_Block(uart_module_t uart_n,  uint16_t n_bytes, uint8_t data[]);

/**
  * @brief Función para transmitir una cadena de caracteres por un módulo UART.
  * @param uart_n Módulo UART correspondiente (UART0, UART1, UART2, UART3).
  * @param str Cadena de caracteres que se desea transmitir.
  * @return Si la cadena se logró almacenar o no en el buffer de transmisión.
  * @details La función guarda una cadena en el buffer de transmisión, siempre 
  * y cuando éste cuente con espacio disponible. Si hay espacio en el buffer
  * y la cadena se logra almacenar, la función retorna VERDADERO; de lo 
  * contrario, si el buffer se encuentra lleno y la cadena no se logra
  *	almacenar, la función retorna FALSO.\n
  * Ejemplo:
  * @code
    //Transmitir la cadena "Hola mundo." por el UART0.
	UARTn_Tx_String(UART0, "Hola mundo.");
  * @endcode
  */
bool UARTn_Tx_String(uart_module_t uart_n, char str[]);


/**
  * @brief Función para transmitir un número entero por el UART.
  * @param uart_n Módulo UART correspondiente (UART0, UART1, UART2, UART3).
  * @param num Número entero que se desea transmitir (32 bits, con signo).
  * @return Si la cadena se logró almacenar o no en el buffer de transmisión.
  * @details La función convierte un entero a cadena de caracteres y guarda
  * dicha cadena en el buffer de transmisión, siempre y cuando éste cuente 
  * con espacio disponible. Si hay espacio en el buffer y la cadena se logra 
  * almacenar, la función retorna VERDADERO; de lo contrario, si el buffer se 
  * encuentra lleno y la cadena no se logra almacenar, la función retorna
  * FALSO.\n
  * Ejemplo:
  * @code
    //Transmitir una cuenta, desde 0 hasta 15, por el UART0.
	int32_t cuenta;
	
	for(cuenta = 0; cuenta <= 15; cuenta++)
	{
		UARTn_Tx_Integer(UART0, cuenta); //Transmitir el valor de la cuenta
		UARTn_Tx_String("\n\r"); //Transmitir un salto de línea
		_delay_ms(1000); // Esperar un segundo
	}
  * @endcode
  */
bool UARTn_Tx_Integer(uart_module_t uart_n, int32_t num);

/**
  * @brief Función para consultar si el buffer de transmisión está lleno.
  * @param uart_n Módulo UART correspondiente (UART0, UART1, UART2, UART3).
  * @return Si el buffer de transmisión se encuentra lleno o no.
  * @details Si el buffer de transmisión se encuentra lleno, la función 
    retorna el valor VERDADERO; de lo contrario, la función retorna FALSO.\n 
  * Ejemplo:
  * @code
	if(UARTn_Tx_Buffer_Full(UART1))
	{
		//Hacer algo si el buffer de transmisión del UART1 está lleno.
	}
  * @endcode
  */
bool UARTn_Tx_Buffer_Full(uart_module_t uart_n);

/**
  * @brief Función para consultar si el buffer de transmisión está vacío.
  * @param uart_n Módulo UART correspondiente (UART0, UART1, UART2, UART3).
  * @return Si el buffer de transmisión se encuentra vacío o no.
  * @details Si el buffer de transmisión se encuentra vacío, la función 
    retorna el valor VERDADERO; de lo contrario, la función retorna FALSO.\n 
  * Ejemplo:
  * @code
  if(UARTn_Tx_Buffer_Full(UART2))
  {
	  //Hacer algo si el buffer de transmisión del UART2 está vacío.
  }
  * @endcode
  */
bool UARTn_Tx_Buffer_Empty(uart_module_t uart_n);

/**
  * @brief Función para leer un byte desde un módulo UART.
  * @param uart_n Módulo UART correspondiente (UART0, UART1, UART2, UART3).
  * @param byte Puntero a la variable donde se guardará el dato leído.
  * @return Si el byte se logró leer o no desde el buffer de recepción.
  * @details La función extrae un byte desde el buffer de recepción, siempre
  * y cuando éste no se encuentre vacío. Si hay algún dato para leer en el 
  * buffer, la función retorna VERDADERO; de lo contrario, si el buffer se 
  * encuentra vacío, la función retorna FALSO.\n  
  * Ejemplo:
  * @code
	char dato;
    //Extraer un byte del buffer de recepción del UART3.
	UARTn_Rx_Byte(UART3, &dato);
  * @endcode
  */
bool UARTn_Rx_Byte(uart_module_t uart_n, char *byte);

/**
  * @brief Función para limpiar el buffer de recepción de un UART.
  * @param uart_n Módulo UART correspondiente (UART0, UART1, UART2, UART3).
  * @details Ejemplo:
  * @code
    //Limpiar el buffer de transmisión del UART0
	UARTn_Rx_Buffer_Reset(UART0);
  * @endcode
  */
void UARTn_Rx_Buffer_Reset(uart_module_t uart_n);

/**
  * @brief Función para consultar si el buffer de recepción está lleno.
  * @param uart_n Módulo UART correspondiente (UART0, UART1, UART2, UART3).
  * @return Si el buffer de recepción se encuentra lleno o no.
  * @details Si el buffer de recepción se encuentra lleno, la función 
    retorna el valor VERDADERO; de lo contrario, la función retorna FALSO.\n 
  * Ejemplo:
  * @code
	if(UARTn_Rx_Buffer_Full(UART1))
	{
		//Hacer algo si el buffer de recepción del UART1 está lleno.
	}
  * @endcode
  */
bool UARTn_Rx_Buffer_Full(uart_module_t uart_n);

/**
  * @brief Función para consultar si el buffer de recepción está vacío.
  * @param uart_n Módulo UART correspondiente (UART0, UART1, UART2, UART3).
  * @return Si el buffer de recepción se encuentra vacío o no.
  * @details Si el buffer de recepción se encuentra vacío, la función 
    retorna el valor VERDADERO; de lo contrario, la función retorna FALSO.\n 
  * Ejemplo:
  * @code
  if(UARTn_Rx_Buffer_Full(UART2))
  {
	  //Hacer algo si el buffer de recepción del UART2 está vacío.
  }
  * @endcode
  */
bool UARTn_Rx_Buffer_Empty(uart_module_t uart_n);

/**
  * @brief Función para transmitir por el UART0, de forma automática, los 
  * bytes que se encuentran almacenados en el buffer de transmisión.
  * @details Esta función debe ser llamada en la ISR de la interrupción 
  * por transmisión completada.\n
  * Ejemplo:
  * @code
	ISR(USART0_TX_vect){
		UART0_Tx_ISR_Callback();
	}
  * @endcode
  */
void UART0_Tx_ISR_Callback(void);

/**
  * @brief Función para almacenar, de forma automática, los bytes recibidos
    por el UART0, dentro del buffer de recepción.
  * @details Esta función debe ser llamada en la ISR de la interrupción 
  * por recepción completada.\n
  * Ejemplo:
  * @code
	ISR(USART0_RX_vect){
		UART0_Rx_ISR_Callback();
	}
  * @endcode
  */
void UART0_Rx_ISR_Callback(void);




#endif	/* MT_UART_H */

