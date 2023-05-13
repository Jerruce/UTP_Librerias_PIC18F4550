/* 
 * File:   MT_spi_master.h
 * Author: mtorres
 *
 * Created on 13 de octubre de 2022, 08:26 AM
 */

#ifndef MT_SPI_MASTER_H
#define	MT_SPI_MASTER_H


/* Inclusión de archivos */
#include <xc.h>
#include <stdint.h>

/* Definición de macros */

#define SS  5
#define SCK 1
#define SDI 0
#define SDO 7

#define TRIS_SS     TRISA
#define TRIS_SCK    TRISB
#define TRIS_SDI    TRISB
#define TRIS_SDO    TRISC


/* Definición de tipos */

typedef enum
{
	SPI_DISABLED = 0,
	SPI_ENABLED
}
spi_status_t;


typedef enum{
    MASTER_MODE_F_4 = 0,
    MASTER_MODE_F_16,
    MASTER_MODE_F_64,
    MASTER_MODE_TMR2_DIV_2,
}
spi_clock_source_t;


typedef enum{
	CLK_POLARITY_0 = 0,
	CLK_POLARITY_1 = 1
}
spi_clock_polarity_t;


typedef enum{
	CLK_PHASE_0 = 0,
	CLK_PHASE_1 = 1
}
spi_clock_phase_t;


typedef enum{
    DISABLE_PORT_MASTER = 0,
    ENABLE_PORT_MASTER
}
spi_master_port_enable_t;


typedef struct{
    spi_status_t spi_status;
    spi_clock_source_t clk_source;
	spi_clock_polarity_t clk_pol;
	spi_clock_phase_t clk_phase;    
}
spi_t;


/* Declaración de funciones */
void SPI_Master_Configure(spi_t *spi_param);
uint8_t SPI_Master_Tx_Byte(uint8_t byte);
void SPI_Master_Tx_Bitstream(uint8_t n_bytes, uint8_t *output_buffer, uint8_t *input_buffer);

#endif	/* MT_SPI_MASTER_H */

