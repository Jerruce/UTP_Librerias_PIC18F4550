
/* Inclusión de archivos */
#include "MT_i2c.h"

/* Definición de funciones */


static void I2C1_Configure(i2c_config_t *i2c_param)
{
    /* Inicialziar los registros de configuración */
    SSPCON1 = 0;
    SSPCON2 = 0;
    SSPSTAT = 0;
    
    /* Configurar el bus I2C en Modo Maestro o Modo Esclavo */
    if(i2c_param->i2c_mode == I2C_MASTER_MODE)
    {
        /* En Modo Maestro ... */
        SSPCON1bits.SSPM = 0b1000;    
        /* Configurar la frecuencia de SCL */
        SSPADD = ((i2c_param->i2c_fosc / i2c_param->i2c_scl_freq) - 1) / 4;
    }
    else
    {
        /* En Modo Esclavo ... */
        SSPCON1bits.SSPM = 0b0110;
        /* Configurar la dirección de esclavo I2C */
        SSPADD = i2c_param->i2c_slave_addr;
        /* Configurar la máscara para la dirección de esclavo */
        SSPCON2 &= ~0b00111110;
        SSPCON2 |= i2c_param->i2c_slave_addr_mask & 0b00111110; 
    }
    
    /* Configurar elcontrolador de Slew Rate */
    SSPSTATbits.SMP = i2c_param->i2c_slew_rate_control_en & 1;
    
    /* Habilitar la interrupción por evento de I2C, de ser el caso */
    PIE1bits.SSPIE = i2c_param->i2c_interrupt & 1;
    
   /* Habilitar el bus I2C, de ser el caso */
    SSPCON1bits.SSPEN = i2c_param->i2c_en & 1;
    
}


void I2Cn_Configure(i2c_config_t *i2c_param)
{
    switch(i2c_param->i2c_module)
    {
        case I2C1_MOD:
            I2C1_Configure(i2c_param);
            break;
        
        default:
            break;
    }
}


uint8_t I2Cn_Master_Start_Condition(i2c_module_t i2c_n)
{
    uint8_t i2c_output = I2C_OK;
    
    switch(i2c_n)
    {
        case I2C1_MOD:
            
            /* Limpiar la bandera de eventos en el bus I2C */
            PIR1bits.SSPIF = 0; 
            /* Enviar una condición de START */
            SSPCON2 &= ~0x01F;
            SSPCON2bits.SEN = 1;
            /* Esperar a que la transmisión se complete */
            while(PIR1bits.SSPIF == 0)
            {
                /* No hacer nada */
            }
            
            /* Verificar la condición de START */
            if(SSPCON2bits.SEN == 1)
            {
                i2c_output = I2C_ERROR;
            }            
                        
            break;
            
        default:
            i2c_output = I2C_ERROR;
            break;
    }
    
    return i2c_output;
}


uint8_t I2Cn_Master_Restart_Condition(i2c_module_t i2c_n)
{
    uint8_t i2c_output = I2C_OK;
    
    switch(i2c_n)
    {
        case I2C1_MOD:
            
            /* Limpiar la bandera de eventos en el bus I2C */
            PIR1bits.SSPIF = 0; 
            /* Enviar una condición de START */
            SSPCON2 &= ~0x01F;
            SSPCON2bits.RSEN = 1;
            /* Esperar a que la transmisión se complete */
            while(PIR1bits.SSPIF == 0)
            {
                /* No hacer nada */
            }
            
            /* Verificar la condición de START */
            if(SSPCON2bits.RSEN == 1)
            {
                i2c_output = I2C_ERROR;
            }            
                        
            break;
            
        default:
            i2c_output = I2C_ERROR;
            break;
    }
    
    return i2c_output;
}



uint8_t I2Cn_Master_Tx_Address(i2c_module_t i2c_n, uint8_t slave_address, i2c_address_mode_t addr_mode)
{
	uint8_t i2c_output = I2C_OK;

    switch(i2c_n)
    {
        case I2C1_MOD:
            
            /* Limpiar la bandera de eventos en el bus I2C */
            PIR1bits.SSPIF = 0; 
            
            /* Cargar la dirección del esclavo e iniciar la transmisión */
            if(addr_mode == I2C_ADDR_READ_MODE){
                SSPBUF = (slave_address << 1) | 0x01;	
            }else{
                SSPBUF = (slave_address << 1) & 0xFE;
            }
   
            /* Esperar a que la transmisión inicie */
            while(SSPSTATbits.RW == 0)
            {
                /* No hacer nada */
            }             
            
            /* Esperar a que la transmisión se complete */
            while(PIR1bits.SSPIF == 0)
            {
                /* No hacer nada */
            }    
            

            /* Verificar si se recibió un ACK o un NACK */
            if(SSPCON2bits.ACKSTAT == 1)
            {
               i2c_output = I2C_ERROR;
            }                
           
            break;
            
        default:
            i2c_output = I2C_ERROR;
            break;
    }
    
    return i2c_output;
            
}


uint8_t I2Cn_Master_Tx_Byte(i2c_module_t i2c_n, uint8_t byte)
{
	uint8_t i2c_output = I2C_OK;

    switch(i2c_n)
    {
        case I2C1_MOD:
            
            /* Limpiar la bandera de eventos en el bus I2C */
            PIR1bits.SSPIF = 0; 
            
            /* Cargar el dato e iniciar la transmisión */
            SSPBUF = byte;	
            
            /* Esperar a que la transmisión inicie */
            while(SSPSTATbits.RW == 0)
            {
                /* No hacer nada */
            }             
            
            /* Esperar a que la transmisión se complete */
            while(PIR1bits.SSPIF == 0)
            {
                /* No hacer nada */
            }    
            

            /* Verificar si se recibió un ACK o un NACK */
            if(SSPCON2bits.ACKSTAT == 1)
            {
               i2c_output = I2C_ERROR;
            }                
           
            break;
            
        default:
            i2c_output = I2C_ERROR;
            break;
    }
    
    return i2c_output;    
}


uint8_t I2Cn_Master_Rx_Byte_ACK(i2c_module_t i2c_n, uint8_t *byte_p)
{

	uint8_t i2c_output = I2C_OK;
    
    switch(i2c_n)
    {
        case I2C1_MOD:
            
            /* Limpiar la bandera de eventos en el bus I2C */
            PIR1bits.SSPIF = 0; 
            
            /* Limpiar la bandera del buffer de recepción */
            SSPSTATbits.BF = 0;
            
            /* Colocar al Maestro en modo lectura */
            SSPCON2 &= ~0x01F;
            SSPCON2bits.RCEN = 1;
            
             /* Esperar a que la recepción se complete */
            while(PIR1bits.SSPIF == 0)
            {
                /* No hacer nada */
            }             
            
            /* Verificar la recepcion */
            if(SSPSTATbits.BF == 1)
            {
                *byte_p = SSPBUF;
            }
            else
            {
                i2c_output = I2C_ERROR;
            }
            
            if(i2c_output != I2C_ERROR)
            {
                /* Limpiar la bandera de eventos en el bus I2C */
                PIR1bits.SSPIF = 0;     
                
                /* Generar un ACK */
                SSPCON2bits.ACKDT = 0;
                SSPCON2 &= ~0x01F;
                SSPCON2bits.ACKEN = 1;
                /* Esperar a que la transmisión se complete */
                while(PIR1bits.SSPIF == 0)
                {
                    /* No hacer nada */
                }                        
            }
            break;
            
        default:
            
            i2c_output = I2C_ERROR;
            break;
            
    }        
            
	return i2c_output;
}


uint8_t I2Cn_Master_Rx_Byte_NACK(i2c_module_t i2c_n, uint8_t *byte_p)
{

	uint8_t i2c_output = I2C_OK;
    
    switch(i2c_n)
    {
        case I2C1_MOD:
            
            /* Limpiar la bandera de eventos en el bus I2C */
            PIR1bits.SSPIF = 0; 
            
            /* Limpiar la bandera del buffer de recepción */
            SSPSTATbits.BF = 0;
            
            /* Colocar al Maestro en modo lectura */
            SSPCON2 &= ~0x01F;
            SSPCON2bits.RCEN = 1;
            
             /* Esperar a que la recepción se complete */
            while(PIR1bits.SSPIF == 0)
            {
                /* No hacer nada */
            }             
            
            /* Verificar la recepcion */
            if(SSPSTATbits.BF == 1)
            {
                *byte_p = SSPBUF;
            }
            else
            {
                i2c_output = I2C_ERROR;
            }
            
            if(i2c_output != I2C_ERROR)
            {
                /* Limpiar la bandera de eventos en el bus I2C */
                PIR1bits.SSPIF = 0;     
                
                /* Generar un NACK */
                SSPCON2bits.ACKDT = 1;
                SSPCON2 &= ~0x01F;
                SSPCON2bits.ACKEN = 1;
                /* Esperar a que la transmisión se complete */
                while(PIR1bits.SSPIF == 0)
                {
                    /* No hacer nada */
                }                        
            }
            break;
            
        default:
            
            i2c_output = I2C_ERROR;
            break;
            
    }        
            
	return i2c_output;
}


uint8_t I2Cn_Master_Write_Data(i2c_module_t i2c_n, uint8_t slave_addr, uint8_t n_bytes, uint8_t *output_buffer)
{
	uint8_t i2c_output = I2C_OK;
	uint8_t index;

	/* Generar la condición de start */
	i2c_output = I2Cn_Master_Start_Condition(i2c_n);
	
    /* Transmitir dirección del esclavo y modo (lectura o escritura) */
    if(i2c_output != I2C_ERROR){
        i2c_output = I2Cn_Master_Tx_Address(i2c_n, slave_addr, I2C_ADDR_WRITE_MODE);
	}

	/* Transmitir los datos */
	if(i2c_output != I2C_ERROR){
        for(index = 0; index < n_bytes; index++){
            i2c_output = I2Cn_Master_Tx_Byte(i2c_n, *(output_buffer + index));
            if(i2c_output == I2C_ERROR){
                break;
            }
        }
	}
    
    /* Generar la condición de STOP */
	if(i2c_output != I2C_ERROR){
		i2c_output = I2Cn_Master_Stop_Condition(i2c_n);	
	}
    
	return i2c_output;    
}



uint8_t I2Cn_Master_Read_Data(i2c_module_t i2c_n, uint8_t slave_addr, uint8_t n_bytes, uint8_t *input_buffer)
{
 	uint8_t i2c_output = I2C_OK;
	uint8_t index;

	/* Generar la condición de START */
	i2c_output = I2Cn_Master_Start_Condition(i2c_n);
    
    
    /* Transmitir dirección del esclavo y modo (lectura) */
	if(i2c_output != I2C_ERROR){
		i2c_output = I2Cn_Master_Tx_Address(i2c_n, slave_addr, I2C_ADDR_READ_MODE);
	}
	
	
	/* Transmitir los datos */
	if(i2c_output != I2C_ERROR){
        
        for(index = 0; index < n_bytes; index++){

            if(index < (n_bytes - 1)){
                i2c_output = I2Cn_Master_Rx_Byte_ACK(i2c_n, input_buffer + index);
            }else{
                i2c_output = I2Cn_Master_Rx_Byte_NACK(i2c_n, input_buffer + index);
            }

            if(i2c_output == I2C_ERROR){
                break;
            }
        }		
	}

	/* Generar la condición de STOP */
	if(i2c_output == I2C_ERROR){
		i2c_output = I2Cn_Master_Stop_Condition(i2c_n);;
	}

	return i2c_output;   
}


uint8_t I2Cn_Master_Stop_Condition(i2c_module_t i2c_n)
{

	uint8_t i2c_output = I2C_OK;
    
    switch(i2c_n)
    {
        case I2C1_MOD:
            
            /* Limpiar la bandera de eventos en el bus I2C */
            PIR1bits.SSPIF = 0; 
            /* Limpiar los 5 bits LSB de SSPCON2 */
            SSPCON2 &= ~0x01F;
            /* Enviar una condición de STOP */
            SSPCON2bits.PEN = 1;
            /* Esperar a que la transmisión se complete */
            while(PIR1bits.SSPIF == 0)
            {
                /* No hacer nada */
            }
            
            /* Verificar la condición de STOP */
            if(SSPCON2bits.PEN == 1)
            {
                i2c_output = I2C_ERROR;
            }
            
            break;
            
        default:    
            i2c_output = I2C_ERROR;
            break;    
    }
    
   
	return i2c_output;    

}
