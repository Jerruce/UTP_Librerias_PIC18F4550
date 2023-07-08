
/* Inclusión de archivos */
#include "MT_uart.h"


/* Definición de funciones */

void UART0_Configure(uart_t *uart_param)
{
    uint32_t my_spbrg = 0;
    
    /* Limpiar los registros */
    TXSTA = 0;
    RCSTA = 0;
    BAUDCON = 0;
    
      /* Configurar el pin de TX como salida y el pin de RX como entrada */
    TRISCbits.RC6 = 0;
    TRISCbits.RC7 = 1;  
    
    /*  Generador de baudios de 16 bits y alta velocidad activada */
    TXSTAbits.BRGH = 1;
    BAUDCONbits.BRG16 = 1;
    
    /* Configurar el baudrate deseado */
    my_spbrg = ((F_OSC / uart_param->baud_rate) / 4) - 1;
    SPBRGH = (my_spbrg >> 8) & 0xFF;
    SPBRG = my_spbrg & 0xFF;
    
    /* Configurar el EUSART para trabajar en modo ASINCRONO */
    TXSTAbits.SYNC = 0;
    
    /* Habilitar el EUSART */
    RCSTAbits.SPEN = 1;
    /* Habilitar/deshabilitar la transmisión */
    if(uart_param->tx_status == UART_TX_ENABLED)
    {
        TXSTAbits.TXEN = 1;
    }
    else
    {
        TXSTAbits.TXEN = 0;
    }
    
    /* Configurar el número de bits de datos */
    if(uart_param->data_bits == UART_9_DATA_BITS)
    {
        TXSTAbits.TX9 = 1;
        RCSTAbits.RX9 = 1;        
    }
    else
    {
        TXSTAbits.TX9 = 0;
        RCSTAbits.RX9 = 0;
    }
    
    /* Habilitar/deshabilitar la recepción */
    if(uart_param->tx_status == UART_RX_ENABLED)
    {
        RCSTAbits.CREN = 1; 
    }
    else
    {
        RCSTAbits.CREN = 0; 
    }    
    
    /* Habilitar/deshabilitar la interrupción por recepción serial completada */
    if(uart_param->rx_interrupt == UART_RX_INTERRUPT_ENABLED)
    {
        PIE1bits.RCIE = 1;
    }
    else
    {
        PIE1bits.RCIE = 0;
    }
  
    /* Habilitar/deshabilitar la interrupción por transmisión serial completada */
    if(uart_param->tx_interrupt == UART_TX_INTERRUPT_ENABLED)
    {
        PIE1bits.TXIE = 1;
    }
    else
    {
        PIE1bits.TXIE = 0;
    }   
       
}


void UARTn_Tx_Byte(uart_module_t uart_n, char byte)
{
    
    switch(uart_n)
    {
        case UART0:
            while(TXSTAbits.TRMT == 0){
                /* Esperar hasta que la transmisión anterior se haya completado */
            }
            /* Cargar el dato al registro TXREG */
            TXREG = byte;            
            break;
            
        default:
            break;
    }
    
    

}


void UARTn_Tx_String(uart_module_t uart_n, char str[])
{
    
    uint8_t indice = 0;
    
    /* Transmitir hasta encontrar el caracter nulo */
    while(str[indice] != '\0'){
        UARTn_Tx_Byte(uart_n, str[indice]);
        indice++;
    }
    
}


void UARTn_Tx_Integer(uart_module_t uart_n, int32_t num)
{

	char signo_y_digitos[12];
	uint8_t signo = 0;
	int32_t digito;
	int8_t indice = 11;

	/* Determinar el signo del número */
	if(num < 0){
		signo = 1;
		num = -num;
	}

	/* Indicar el fin de la cadena de caracteres */
	signo_y_digitos[indice--] = '\0';

	/* Extraer los dígitos uno a uno, empezando por las unidades */
	do{
		digito = (num % 10) + '0';
		signo_y_digitos[indice--] = (char)digito;
		num /= 10;
	}while(num != 0);

	/* Agregar el signo (de ser necesario) */
	if(signo){
		signo_y_digitos[indice] = '-';
	}else{
		indice++;
	}

	/* Transmitir el número */
	UARTn_Tx_String(uart_n, &signo_y_digitos[indice]);
}