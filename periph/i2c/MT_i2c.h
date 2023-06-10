/* 
 * File:   MT_i2c.h
 * Author: mtorres
 *
 * Created on 3 de junio de 2023, 03:27 AM
 */

#ifndef MT_I2C_H
#define	MT_I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

/* Inclusión de arhivos */
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>  

    
/* Definición de macros */

#define I2C_OK					0x00
#define I2C_ERROR				0x01    
    

/**
  * @brief Módulos I2C disponibles en el microcontrolador.
  */    
typedef enum
{
	I2C1_MOD = 0  /**< Módulo I2C1. */           
}
i2c_module_t;    
    

/**
  * @brief Modos de la trama.
  */  
typedef enum
{
    I2C_ADDR_WRITE_MODE = 0, /**< Modo trama de escritura. */ 
    I2C_ADDR_READ_MODE /**< Modo trama de lectura. */        
}
i2c_address_mode_t;


/**
  * @brief Habilitación/deshabilitación del módulo I2C.
  */
typedef enum
{
	I2C_DISABLED = 0, /**< Habilitar el módulo I2C. */
	I2C_ENABLED /**< Deshabilitar el módulo I2C. */
}
i2c_status_t;


/**
  * @brief Valores estándar de frecuencia para la señal de reloj (SCL).
  */
typedef enum
{
	I2C_SCL_FREQ_100_KHZ = 100000UL, /**< Frecuencia de SCL: 100 KHz. */
	I2C_SCL_FREQ_400_KHZ = 400000UL, /**< Frecuencia de SCL: 400 KHz. */
    I2C_SCL_FREQ_1_MHZ = 1000000UL /**< Frecuencia de SCL: 1 MHz. */        
}
i2c_scl_freq_t;


/**
  * @brief Módulo I2C en modo Esclavo o Maestro.
  */
typedef enum
{
	I2C_SLAVE_MODE = 0, /**< Habilitar el módulo I2C. */
	I2C_MASTER_MODE /**< Deshabilitar el módulo I2C. */
}
i2c_mode_t;


/**
  * @brief Habilitación/deshabilitación del control de Slew Rate.
  */
typedef enum
{
    I2C_SLEW_RATE_CONTROL_ENABLED = 0, /**< Habilita el control de slew rate. */ 
    I2C_SLEW_RATE_CONTROL_DISABLED /**< Deshabilita el control de slew rate. */ 
}
i2c_slew_rate_control_t;


/**
  * @brief Habilitación/deshabilitación de interrupción por llamada
  * general (cuando se trabaja en modo esclavo). 
  */
typedef enum
{
    I2C_GENERAL_CALL_DISABLED = 0, /**< Deshabilita la interrupción por recepción. */
    I2C_GENERAL_CALL_ENABLED /**< Habilita interrupción por recepción. */        
}
i2c_general_call_status_t;


/**
  * @brief Habilitación/deshabilitación de la función de clock stretching
  * en la comunicación I2C cuando se trabaja en modo esclavo. 
  */
typedef enum
{
    I2C_CLOCK_STRETCHING_DISABLED = 0, /**< Deshabilita la función de clock stretching. */
    I2C_CLOCK_STRETCHING_ENABLED /**< Habilita la función de clock stretching. */        
}
i2c_clock_stretching_status_t;


/**
  * @brief Habilitación/deshabilitación de la función de la interrupción por
  * eventos en el bus I2C. 
  */
typedef enum
{
    I2C_INTERRUPT_DISABLED = 0,
    I2C_INTERRUPT_ENABLED  
}
i2c_interrupt_status_t;


/**
  * @brief Esctructura para representar los parámetros de configuración de 
  * del módulo I2C.
  */
typedef struct
{
    uint32_t i2c_fosc; /**< Frecuencia de reloj que llega al módulo I2C. */
    i2c_module_t i2c_module; /**< Módulo I2C que se desea configurar. */
    i2c_scl_freq_t i2c_scl_freq; /**< Frecuencia de la señal de reloj SCL (en modo maestro). */    
    i2c_status_t i2c_en; /**< Habilitar/deshabilitar el módulo I2C. */
    i2c_mode_t i2c_mode; /**< Configurar como Maestro o Esclavo */
    uint8_t i2c_slave_addr; /**< Dirección I2C (modo Esclavo) */
    uint8_t i2c_slave_addr_mask; /**< Máscara para la dirección I2C (modo Esclavo) */
    i2c_clock_stretching_status_t i2c_slave_clock_stretch;
    i2c_slew_rate_control_t i2c_slew_rate_control_en;
    i2c_general_call_status_t i2c_slave_call_interrupt;
    i2c_interrupt_status_t i2c_interrupt; /**< Habilitar/deshabilitar las interrupciones. */
}
i2c_config_t;


/* Declaración de funciones */
void I2Cn_Configure(i2c_config_t *i2c_param);
uint8_t I2Cn_Master_Start_Condition(i2c_module_t i2c_n);
uint8_t I2Cn_Master_Restart_Condition(i2c_module_t i2c_n);
uint8_t I2Cn_Master_Tx_Address(i2c_module_t i2c_n, uint8_t slave_address, i2c_address_mode_t addr_mode);
uint8_t I2Cn_Master_Tx_Byte(i2c_module_t i2c_n, uint8_t byte);
uint8_t I2Cn_Master_Rx_Byte_ACK(i2c_module_t i2c_n, uint8_t *byte_p);
uint8_t I2Cn_Master_Rx_Byte_NACK(i2c_module_t i2c_n, uint8_t *byte_p);
uint8_t I2Cn_Master_Write_Data(i2c_module_t i2c_n, uint8_t slave_addr, uint8_t n_bytes, uint8_t *output_buffer);
uint8_t I2Cn_Master_Read_Data(i2c_module_t i2c_n, uint8_t slave_addr, uint8_t n_bytes, uint8_t *input_buffer);
uint8_t I2Cn_Master_Stop_Condition(i2c_module_t i2c_n);    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* MT_I2C_H */

