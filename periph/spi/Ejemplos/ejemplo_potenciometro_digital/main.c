/*
 * File:   main.c
 * Author: mtorres
 *
 * Created on 24 de septiembre de 2022, 11:51 AM
 */

/* Inclusión de archivos */
#include "system_config.h"
#include <xc.h>
#include <stdint.h>
#include"MT_spi_master.h"


/* Definición de macros */
#define TRIS_SS_DIG_POT     TRISDbits.RD0
#define LAT_SS_DIG_POT      LATDbits.LATD0
    

/* Definición de variables */
uint8_t spi_buff_escritura[20];
uint8_t spi_buff_lectura[20];

/* Declaración de funciones */
void SPI_Inicializar(void);

/* Función principal */
int main(void){
       
    /* Configurar como salida  e inicializar el pin SS para el
     * potenciómetro digital */
    TRIS_SS_DIG_POT = 0;
    LAT_SS_DIG_POT = 1;
    
    /* Configurar el módulo SPI en MODO 0 (Polaridad:0, Fase:0) */
    SPI_Inicializar();
    
    /* Configurar el potenciómetro al mínimo de su valor */

    /* Construir la trama que se va a transmitir */
    spi_buff_escritura[0] = 0b00010001; /* Comando escribir */
    spi_buff_escritura[1] = 128; /* Valor --> MAX: 255, Mitad: 128 */
    /* Habilitar la comunicación con el potenciómetro digital (esclavo)*/
    LAT_SS_DIG_POT = 0;    
    /* Transmitir la trama (2 bytes) */
    SPI_Master_Tx_Bitstream(2, spi_buff_escritura, spi_buff_lectura);
    /* Deshabilitar la comunicación con el potenciómetro digital (esclavo)*/
    LAT_SS_DIG_POT = 1;
    
    while(1)
    {
          
        
    }
    
    return 0;
}

/* Definición de funciones */
void SPI_Inicializar(void)
{
    spi_t my_spi;
    
    my_spi.spi_status = SPI_ENABLED;
    my_spi.clk_source = MASTER_MODE_F_64;
    my_spi.clk_pol = CLK_POLARITY_0;
    my_spi.clk_phase = CLK_PHASE_0;
    
    SPI_Master_Configure(&my_spi);
}

