
/* Inclusión de archivos */
#include "MT_spi_master.h"

/* Definición de funciones */

void SPI_Master_Configure(spi_t *spi_param){
	
    /* Configurar el pin SDI como entrada */
    TRIS_SDI |= (1<< SDI);
    
    /* Configurar los pines SCK y SDO como salida */
    TRIS_SCK &= ~(1 << SCK);
    TRIS_SDO &= ~(1 << SDO);
    
    /* Configurar SPI en modo Maestro y elegir fuente de reloj */
    SSPCON1bits.SSPM = (spi_param->clk_source) & 0x03;

    /* Configurar la polaridad de la señal de reloj */
    if(spi_param->clk_pol == CLK_POLARITY_1)
    {
       SSPCON1bits.CKP = 1; 
    }
    else
    {
        SSPCON1bits.CKP = 0; 
    }
    
    /* Configurar la fase de la señal de reloj */
     if(spi_param->clk_phase == CLK_PHASE_1)
    {
       SSPSTATbits.CKE = 1; 
    }
    else
    {
        SSPSTATbits.CKE = 0; 
    }  
    
    // Activar puerto
    if(spi_param->spi_status == SPI_ENABLED)
    {
         SSPCON1bits.SSPEN = 1;
    }
    else
    {
        SSPCON1bits.SSPEN = 0;
    }
    
    
    //Leer bit en el medio de tiempo de salida
    SSPSTATbits.SMP = 0; 
}



uint8_t SPI_Master_Tx_Byte(uint8_t byte)
{    
	uint8_t miso_data;
    
	/* Iniciar transferencia */
	SSPBUF = byte;
    
	/* Esperar a que la transferencia se complete */
	while(!SSPSTATbits.BF){
		// No hacer nada (blocking polling)
	}
    
	/* Almacenar el byte recibido */
	miso_data = SSPBUF;
    
	return miso_data;    
   
}


void SPI_Master_Tx_Bitstream(uint8_t n_bytes, uint8_t *output_buffer, uint8_t *input_buffer)
{
    uint8_t indice;

	for(indice = 0; indice < n_bytes; indice++){
		/* Iniciar transferencia */
		SSPBUF = *(output_buffer + indice);
		/* Esperar a que la transferencia se complete */
		while(SSPSTATbits.BF == 0){
			// No hacer nada (blocking polling)
		}
		/* Almacenar el byte recibido en el buffer de recepción */
		*(input_buffer + indice) = SSPBUF;
	}
}