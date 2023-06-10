/*
 * File:   main.c
 * Author: mtorres
 *
 * Created on 3 de junio de 2023, 03:22 AM
 */

/* INclusión de archivos */
#include "system_config.h"
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "MT_i2c.h"
#include "MT_uart.h"
#include "MT_mpu6050.h"


/* Definicón  de variables */

volatile char tx_buffer[50];

int16_t ax_bin; /**< Componente de la aceleración en el eje X (binario). */
int16_t ay_bin; /**< Componente de la aceleración en el eje Y (binario). */
int16_t az_bin; /**< Componente de la aceleración en el eje Z (binario). */


/* Declaración de funciones */
void I2C_Initialize(void);
void UART0_Initialize(void);
uint8_t MPU6050_Inititalize(void);


/* Función principal */
void main(void) {
    
    uint8_t aux = I2C_OK;
    
    /* Inicializar los periféricos internos y externos */
    UART0_Initialize();
    I2C_Initialize();
    aux = MPU6050_Inititalize();
    
    /* Verificar si se logró inicializar el MPU6050 */
    if(aux == I2C_OK)
    {
        UARTn_Tx_String(UART0, "IMU inicializado correctamente.\n\r");
    }
    else
    {
        UARTn_Tx_String(UART0, "IMU no se pudo inicializar.\n\r");
    }
    
    /* Repetir indefinidamente */
    while(1)
    {
        /* Esperar un segundo */
        __delay_ms(1000);
        /* Medir la aceleración */
        aux = MPU6050_Read_Accelerometer();
        
        if(aux == I2C_OK){

            /* Leer las componentes de aceleración en formato binario */
            MPU6050_Get_Accelerometer_Output(&ax_bin, &ay_bin, &az_bin);

            /* Iprimir los valores de aceleración */
            UARTn_Tx_String(UART0, "ax: ");
            UARTn_Tx_Integer(UART0, ax_bin);
            UARTn_Tx_String(UART0, "\n\r");
            
            UARTn_Tx_String(UART0, "ax: ");
            UARTn_Tx_Integer(UART0, ay_bin);
            UARTn_Tx_String(UART0, "\n\r");

            UARTn_Tx_String(UART0, "ax: ");
            UARTn_Tx_Integer(UART0, az_bin);
            UARTn_Tx_String(UART0, "\n\r");            

        }
        else
        {
            UARTn_Tx_String(UART0, "Error al leer IMU.\n\n\r");
        }
        
    }
    
    return;
}


void I2C_Initialize(void)
{
    i2c_config_t my_i2c;
    
    my_i2c.i2c_fosc = 20000000UL;
    my_i2c.i2c_module = I2C1_MOD;
    my_i2c.i2c_en = I2C_ENABLED;
    my_i2c.i2c_mode = I2C_MASTER_MODE;
    my_i2c.i2c_scl_freq = I2C_SCL_FREQ_100_KHZ;
    my_i2c.i2c_slew_rate_control_en = I2C_SLEW_RATE_CONTROL_DISABLED;
    my_i2c.i2c_interrupt = I2C_INTERRUPT_DISABLED;
    
    I2Cn_Configure(&my_i2c);
}


void UART0_Initialize(void){
	
	uart_t my_uart;
	
	my_uart.baud_rate = BAUD_115200_BPS;
	my_uart.data_bits = UART_8_DATA_BITS;
	my_uart.tx_status = UART_TX_ENABLED;
	my_uart.rx_status = UART_RX_DISABLED;
    my_uart.tx_interrupt = UART_TX_INTERRUPT_DISABLED;
	my_uart.rx_interrupt = UART_RX_INTERRUPT_DISABLED;
    
	UART0_Configure(&my_uart);
}

uint8_t MPU6050_Inititalize(void){
	
	MPU6050_Config_t my_imu;
	uint8_t salida = I2C_OK;
	
	my_imu.clock_source = INTERNAL_8_MHZ_OSCILLATOR;
	my_imu.sample_rate_divider = 0;
	my_imu.external_frame_synchronization = INPUT_DISABLED;
	my_imu.accel_full_scale_range = ACCEL_FS_4G;
	my_imu.gyro_full_scale_range = GYRO_FS_1000_DEG_PER_SEC;
	my_imu.digital_low_pass_filter = DLPF_5_HZ;
	
	salida = MPU6050_Configure(&my_imu);
	
	return salida;
}