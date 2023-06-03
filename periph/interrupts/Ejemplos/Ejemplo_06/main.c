/*
 * File:   main.c
 * Author: mtorres
 *
 * Created on 24 de septiembre de 2022, 11:51 AM
 */

/* Inclusión de archivos */
#include "system_config.h"
#include <xc.h>
#include "MT_uart.h" 
#include "MT_timer.h"

/* Definición de macros */

/* Definición de variables */
volatile char caracter_recibido = '\0';
volatile uint8_t recepcion_completa = 0;
volatile uint8_t transmitir_mensaje_uart = 0;

/* Declaración de funciones */
void UART_Inicializar(void);
void Interpretar_Comando(void);
void Timer0_Inicializar(void);

/* Función principal */
int main(void){
    /* Configurar el PUERTO D como salida */
    TRISD = 0x00;
    /* Configurar el UART */
    UART_Inicializar();
    /* Configurar el Timer0 */
    Timer0_Inicializar();
    /* Habilitar las interrupciones */
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    RCONbits.IPEN = 0;
    
    while(1)
    {
        if(recepcion_completa == 1)
        {
            INTCONbits.GIE = 0;
            recepcion_completa = 0;
            INTCONbits.GIE = 1;
            Interpretar_Comando(); 
        }
        
        if(transmitir_mensaje_uart == 1)
        {
            INTCONbits.GIE = 0;
            transmitir_mensaje_uart = 0;
            INTCONbits.GIE = 1;
            UARTn_Tx_String(UART0, "Hola mundo.\n\r"); 
        }        

    }
    
    return 0;
}

/* Rutina de servicio a interrupciones (ISR) */
__interrupt() void ISR(void)
{
    static uint16_t conta_uart_1ms = 0;
    
    /* Si la interrupción fue causada por recepción del UART ... */
    if(PIR1bits.RCIF == 1)
    {
        /* Almacenar el caracter recibido */
        caracter_recibido = RCREG;
        /* Limpiar la bandera */
        PIR1bits.RCIF = 0;
        /* Indicar que se ha recibido un caracter */
        recepcion_completa = 1;      
    }
    /* Si la interrupción fue causada por desbordamiento del Timer0 ... */
    else if(INTCONbits.TMR0IF == 1)
    {
        Timer0_Reload();
        conta_uart_1ms++;
        if(conta_uart_1ms >= 1000)
        {
            conta_uart_1ms = 0;
            transmitir_mensaje_uart = 1;
        }
    }
    else
    {
        /* No hacer nada */
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
    my_uart.rx_interrupt = UART_RX_INTERRUPT_ENABLED;
    my_uart.tx_interrupt = UART_TX_INTERRUPT_DISABLED;
    
    UART0_Configure(&my_uart);
    
}

void Interpretar_Comando(void)
{
    char comando;
    
    comando = caracter_recibido;
    
    /* Llevar a cabo la acción correspondiente al comando recibido*/
    switch(comando)
    {
        case '0':
            LATDbits.LATD0 = !LATDbits.LATD0;
            break;
            
        case '1':
            LATDbits.LATD1 = !LATDbits.LATD1;
            break;
            
        case '2':
            LATDbits.LATD2 = !LATDbits.LATD2;
            break;
            
        case '3':
            LATDbits.LATD3 = !LATDbits.LATD3;
            break; 
            
        case '4':
            LATDbits.LATD4 = !LATDbits.LATD4;
            break;
            
        case '5':
            LATDbits.LATD5 = !LATDbits.LATD5;
            break;
            
        case '6':
            LATDbits.LATD6 = !LATDbits.LATD6;
            break;
            
        case '7':
            LATDbits.LATD7 = !LATDbits.LATD7;
            break;    
            
        case 's':
            LATD = 0xFF;
            break;
            
         case 'c':
            LATD = 0x00;
            break; 
            
        case 't':
            LATD ^= 0xFF;
            break;
            
        default:
            break;
            
    }
    
}