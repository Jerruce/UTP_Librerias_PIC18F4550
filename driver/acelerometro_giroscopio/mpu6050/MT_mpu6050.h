/**
  * @file MT_mpu6050.h	
  * @version 1.0
  * @date 05/04/2022
  * @author Miguel Torres
  * @brief  Archivo cabecera con macros, enumeraciones, estructuras y 
  * funciones para el manejo del IMU MPU6050.   
  */

#ifndef MT_MPU6050_H_
#define MT_MPU6050_H_

/* File inclusion */
#include "MT_i2c.h"

/* MACRO DEFINITION */

/* I2C Module */
#define MPU6050_I2C_MODULE      I2C1_MOD

/* I2C Slave Address */
#define MPU6050_I2C_SLAVE_ADDRESS		0x68

/* I2C BUffer Size */

#define MPU6050_I2C_WRITE_BUFF_SIZE		10
#define MPU6050_I2C_READ_BUFF_SIZE		20

/* Registers */

#define MPU6050_SELF_TEST_X				0x0D	// R/W
#define MPU6050_SELF_TEST_Y				0x0E	// R/W
#define MPU6050_SELF_TEST_Z				0x0F	// R/W
#define MPU6050_SELF_TEST_A				0x10	// R/W
#define MPU6050_SMPLRT_DIV				0x19	// R/W
#define MPU6050_CONFIG					0x1A	// R/W
#define MPU6050_GYRO_CONFIG				0x1B	// R/W
#define MPU6050_ACCEL_CONFIG			0x1C	// R/W
#define MPU6050_FIFO_EN					0x23	// R/W
#define MPU6050_I2C_MST_CTRL			0x24	// R/W
#define MPU6050_I2C_SLV0_ADDR			0x25	// R/W
#define MPU6050_I2C_SLV0_REG			0x26	// R/W
#define MPU6050_I2C_SLV0_CTRL			0x27	// R/W
#define MPU6050_I2C_SLV1_ADDR			0x28	// R/W
#define MPU6050_I2C_SLV1_REG			0x29	// R/W
#define MPU6050_I2C_SLV1_CTRL			0x2A	// R/W
#define MPU6050_I2C_SLV2_ADDR			0x2B	// R/W
#define MPU6050_I2C_SLV2_REG			0x2C	// R/W
#define MPU6050_I2C_SLV2_CTRL			0x2D	// R/W
#define MPU6050_I2C_SLV3_ADDR			0x2E	// R/W
#define MPU6050_I2C_SLV3_REG			0x2F	// R/W
#define MPU6050_I2C_SLV3_CTRL			0x30	// R/W
#define MPU6050_I2C_SLV4_ADDR			0x31	// R/W
#define MPU6050_I2C_SLV4_REG			0x32	// R/W
#define MPU6050_I2C_SLV4_DO				0x33	// R/W
#define MPU6050_I2C_SLV4_CTRL			0x34	// R/W
#define MPU6050_I2C_SLV4_DI				0x35	// R
#define MPU6050_I2C_MST_STATUS			0x36	// R
#define MPU6050_INT_PIN_CFG				0x37	// R/W
#define MPU6050_INT_ENABLE				0x38	// R/W
#define MPU6050_INT_STATUS				0x3A	// R
#define MPU6050_ACCEL_XOUT_H			0x3B	// R
#define MPU6050_ACCEL_XOUT_L			0x3C	// R
#define MPU6050_ACCEL_YOUT_H			0x3D	// R
#define MPU6050_ACCEL_YOUT_L			0x3E	// R
#define MPU6050_ACCEL_ZOUT_H			0x3F	// R
#define MPU6050_ACCEL_ZOUT_L			0x40	// R
#define MPU6050_TEMP_OUT_H				0x41	// R
#define MPU6050_TEMP_OUT_L				0x42	// R
#define MPU6050_GYRO_XOUT_H				0x43	// R
#define MPU6050_GYRO_XOUT_L				0x44	// R
#define MPU6050_GYRO_YOUT_H				0x45	// R
#define MPU6050_GYRO_YOUT_L				0x46	// R
#define MPU6050_GYRO_ZOUT_H				0x47	// R
#define MPU6050_GYRO_ZOUT_L				0x48	// R
#define MPU6050_EXT_SENS_DATA_00		0x49	// R
#define MPU6050_EXT_SENS_DATA_01		0x4A	// R
#define MPU6050_EXT_SENS_DATA_02		0x4B	// R
#define MPU6050_EXT_SENS_DATA_03		0x4C	// R
#define MPU6050_EXT_SENS_DATA_04		0x4D	// R
#define MPU6050_EXT_SENS_DATA_05		0x4E	// R
#define MPU6050_EXT_SENS_DATA_06		0x4F	// R
#define MPU6050_EXT_SENS_DATA_07		0x50	// R
#define MPU6050_EXT_SENS_DATA_08		0x51	// R
#define MPU6050_EXT_SENS_DATA_09		0x52	// R
#define MPU6050_EXT_SENS_DATA_10		0x53	// R
#define MPU6050_EXT_SENS_DATA_11		0x54	// R
#define MPU6050_EXT_SENS_DATA_12		0x55	// R
#define MPU6050_EXT_SENS_DATA_13		0x56	// R
#define MPU6050_EXT_SENS_DATA_14		0x57	// R
#define MPU6050_EXT_SENS_DATA_15		0x58	// R
#define MPU6050_EXT_SENS_DATA_16		0x59	// R
#define MPU6050_EXT_SENS_DATA_17		0x5A	// R
#define MPU6050_EXT_SENS_DATA_18		0x5B	// R
#define MPU6050_EXT_SENS_DATA_19		0x5C	// R
#define MPU6050_EXT_SENS_DATA_20		0x5D	// R
#define MPU6050_EXT_SENS_DATA_21		0x5E	// R
#define MPU6050_EXT_SENS_DATA_22		0x5F	// R
#define MPU6050_EXT_SENS_DATA_23		0x60	// R
#define MPU6050_I2C_SLV0_DO				0x63	// R/W
#define MPU6050_I2C_SLV1_DO				0x64	// R/W
#define MPU6050_I2C_SLV2_DO				0x65	// R/W
#define MPU6050_I2C_SLV3_DO				0x66	// R/W
#define MPU6050_I2C_MST_DELAY_CTRL		0x67	// R/W
#define MPU6050_SIGNAL_PATH_RESET		0x68	// R/W
#define MPU6050_USER_CTRL				0x6A	// R/W
#define MPU6050_PWR_MGMT_1				0x6B	// R/W
#define MPU6050_PWR_MGMT_2				0x6C	// R/W
#define MPU6050_FIFO_COUNTH				0x72	// R/W
#define MPU6050_FIFO_COUNTL				0x73	// R/W
#define MPU6050_FIFO_R_W				0x74	// R/W
#define MPU6050_WHO_AM_I				0x75	// R

/* Bits */

#define BIT_XA_TEST_4				7
#define BIT_XA_TEST_3				6
#define BIT_XA_TEST_2				5
#define BIT_XG_TEST_4				4
#define BIT_XG_TEST_3				3
#define BIT_XG_TEST_2				2
#define BIT_XG_TEST_1				1
#define BIT_XG_TEST_0				0

#define BIT_YA_TEST_4				7
#define BIT_YA_TEST_3				6
#define BIT_YA_TEST_2				5
#define BIT_YG_TEST_4				4
#define BIT_YG_TEST_3				3
#define BIT_YG_TEST_2				2
#define BIT_YG_TEST_1				1
#define BIT_YG_TEST_0				0

#define BIT_ZA_TEST_4				7
#define BIT_ZA_TEST_3				6
#define BIT_ZA_TEST_2				5
#define BIT_ZG_TEST_4				4
#define BIT_ZG_TEST_3				3
#define BIT_ZG_TEST_2				2
#define BIT_ZG_TEST_1				1
#define BIT_ZG_TEST_0				0

#define BIT_XA_TEST_1				5
#define BIT_XA_TEST_0				4
#define BIT_YA_TEST_1				3
#define BIT_YA_TEST_0				2
#define BIT_ZA_TEST_1				1
#define BIT_ZA_TEST_0				0

#define BIT_EXT_SYNC_SET_2			5
#define BIT_EXT_SYNC_SET_1			4
#define BIT_EXT_SYNC_SET_0			3
#define BIT_DLPF_CFG_2				2
#define BIT_DLPF_CFG_1				1
#define BIT_DLPF_CFG_0				0

#define BIT_FS_SEL_1				4
#define BIT_FS_SEL_0				3

#define BIT_XA_ST					7
#define BIT_YA_ST					6
#define BIT_ZA_ST					5
#define BIT_AFS_SEL_1				4
#define BIT_AFS_SEL_0				3

#define BIT_TEMP_FIFO_EN			7
#define BIT_XG_FIFO_EN				6
#define BIT_YG_FIFO_EN				5
#define BIT_ZG_FIFO_EN				4
#define BIT_ACCEL_FIFO_EN			3
#define BIT_SLV2_FIFO_EN			2
#define BIT_SLV1_FIFO_EN			1
#define BIT_SLV0_FIFO_EN			0

#define BIT_MULT_MST_EN				7
#define BIT_WAIT_FOR_ES				6
#define BIT_SLV3_FIFO_EN			5
#define BIT_I2C_MST_P_NSR			4
#define BIT_I2C_MST_CLK_3			3
#define BIT_I2C_MST_CLK_2			2
#define BIT_I2C_MST_CLK_1			1
#define BIT_I2C_MST_CLK_0			0

#define BIT_I2C_SLV0_RW				7

#define BIT_I2C_SLV0_EN				7
#define BIT_I2C_SLV0_BYTE_SW		6
#define BIT_I2C_SLV0_REG_DIS		5
#define BIT_I2C_SLV0_GRP			4
#define BIT_I2C_SLV0_LEN_3			3
#define BIT_I2C_SLV0_LEN_2			2
#define BIT_I2C_SLV0_LEN_1			1
#define BIT_I2C_SLV0_LEN_0			0

#define BIT_I2C_SLV1_RW				7

#define BIT_I2C_SLV1_EN				7
#define BIT_I2C_SLV1_BYTE_SW		6
#define BIT_I2C_SLV1_REG_DIS		5
#define BIT_I2C_SLV1_GRP			4
#define BIT_I2C_SLV1_LEN_3			3
#define BIT_I2C_SLV1_LEN_2			2
#define BIT_I2C_SLV1_LEN_1			1
#define BIT_I2C_SLV1_LEN_0			0

#define BIT_I2C_SLV2_RW				7

#define BIT_I2C_SLV2_EN				7
#define BIT_I2C_SLV2_BYTE_SW		6
#define BIT_I2C_SLV2_REG_DIS		5
#define BIT_I2C_SLV2_GRP			4
#define BIT_I2C_SLV2_LEN_3			3
#define BIT_I2C_SLV2_LEN_2			2
#define BIT_I2C_SLV2_LEN_1			1
#define BIT_I2C_SLV2_LEN_0			0

#define BIT_I2C_SLV3_RW				7

#define BIT_I2C_SLV3_EN				7
#define BIT_I2C_SLV3_BYTE_SW		6
#define BIT_I2C_SLV3_REG_DIS		5
#define BIT_I2C_SLV3_GRP			4
#define BIT_I2C_SLV3_LEN_3			3
#define BIT_I2C_SLV3_LEN_2			2
#define BIT_I2C_SLV3_LEN_1			1
#define BIT_I2C_SLV3_LEN_0			0

#define BIT_I2C_SLV4_RW				7

#define BIT_I2C_SLV4_EN				7
#define BIT_I2C_SLV4_INT_EN			6
#define BIT_I2C_SLV4_REG_DIS		5
#define BIT_I2C_MST_DLY_4			4
#define BIT_I2C_MST_DLY_3			3
#define BIT_I2C_MST_DLY_2			2
#define BIT_I2C_MST_DLY_1			1
#define BIT_I2C_MST_DLY_0			0

#define BIT_PASS_THROUGH			7
#define BIT_I2C_SLV4_DONE			6
#define BIT_I2C_LOST_ARB			5
#define BIT_I2C_SLV4_NACK			4
#define BIT_I2C_SLV3_NACK			3
#define BIT_I2C_SLV2_NACK			2
#define BIT_I2C_SLV1_NACK			1
#define BIT_I2C_SLV0_NACK			0

#define BIT_INT_LEVEL				7
#define BIT_INT_OPEN				6
#define BIT_LATCH_INT_EN			5
#define BIT_INT_RD_CLEAR			4
#define BIT_FSYNC_INT_LEVEL			3
#define BIT_FSYNC_INT_EN			2
#define BIT_I2C_BYPASS_EN			1

#define BIT_FIFO_OFLOW_EN			4
#define BIT_I2C_MST_INT_EN			3
#define BIT_DATA_RDY_EN				0

#define BIT_FIFO_OFLOW_INT			4
#define BIT_I2C_MAST_INT			3
#define BIT_DATA_RDY_INT			0

#define BIT_DELAY_ES_SHADOW			7
#define BIT_I2C_SLV4_DLY_EN			4
#define BIT_I2C_SLV3_DLY_EN			3
#define BIT_I2C_SLV2_DLY_EN			2
#define BIT_I2C_SLV1_DLY_EN			1
#define BIT_I2C_SLV0_DLY_EN			0

#define BIT_GYRO_RESET				2
#define BIT_ACCEL_RESET				1
#define BIT_TEMP_RESET				0

#define BIT_FIFO_EN					6
#define BIT_I2C_MST_EN				5
#define BIT_I2C_IF_DIS				4
#define BIT_FIFO_RESET				2
#define BIT_I2C_MST_RESET			1
#define BIT_SIG_COND_RESET			0

#define BIT_DEVICE_RESET			7
#define BIT_SLEEP					6
#define BIT_CYCLE					5
#define BIT_TEMP_DIS				3
#define BIT_CLKSEL_2				2
#define BIT_CLKSEL_1				1
#define BIT_CLKSEL_0				0

#define BIT_LP_WAKE_CTRL_1			7
#define BIT_LP_WAKE_CTRL_0			6
#define BIT_STBY_XA					5
#define BIT_STBY_YA					4
#define BIT_STBY_ZA					3
#define BIT_STBY_XG					2
#define BIT_STBY_YG					1
#define BIT_STBY_ZG					0

#define ACCEL_SENSITIVITY_FS_2G					16384.0
#define ACCEL_SENSITIVITY_FS_4G					8192.0
#define ACCEL_SENSITIVITY_FS_8G					4096.0
#define ACCEL_SENSITIVITY_FS_16G				2048.0

#define GYRO_SENSITIVITY_FS_250_DEG_S			131.0
#define GYRO_SENSITIVITY_FS_500_DEG_S			65.5
#define GYRO_SENSITIVITY_FS_1000_DEG_S			32.8
#define GYRO_SENSITIVITY_FS_2000_DEG_S			16.4

#define TEMPERATURE_SENSITIVITY					40.0
#define TEMPERATURE_OFFSET						-521

#define GRAVITY_ACCEL_M_PER_S2					9.81

/**
  * @brief Opciones de sincronización externa.
  */
typedef enum{
	INPUT_DISABLED = 0, /**< Sincronización externa deshabilitada. */
	TEMP_OUT_L0,	/**< Sincronización externa mediante la salida de 
	                     temperatura. */
	GYRO_XOUT_L0, /**< Sincronización externa mediante la salida X del 
	                   giroscopio. */
	GYRO_YOUT_L0, /**< Sincronización externa mediante la salida Y del 
					   giroscopio. */
	GYRO_ZOUT_L0, /**< Sincronización externa mediante la salida Z del 
				       giroscopio. */
	ACCEL_XOUT_L0, /**< Sincronización externa mediante la salida X del 
	                    acelerómetro. */
	ACCEL_YOUT_L0, /**< Sincronización externa mediante la salida Y del 
					    acelerómetro. */
	ACCEL_ZOUT_L0 /**< Sincronización externa mediante la salida Z del 
					   acelerómetro. */
}MPU6050_External_Frame_Synchronization_t;

/**
  * @brief Configuración del filtro pasa-bajo digital que viene 
  * incorporado en el MPU6050.
  */
typedef enum{
	DLPF_257_HZ = 0, /**< Filtro pasa-bajo digital con frecuencia de corte 
	                      257 Hz, aproximadamente. */
	DLPF_186_HZ, /**< Filtro pasa-bajo digital con frecuencia de corte 
					  186 Hz, aproximadamente. */
	DLPF_96_HZ, /**< Filtro pasa-bajo digital con frecuencia de corte 
				     96 Hz, aproximadamente. */
	DLPF_43_HZ, /**< Filtro pasa-bajo digital con frecuencia de corte
				     43 Hz, aproximadamente. */
	DLPF_20_HZ, /**< Filtro pasa-bajo digital con frecuencia de corte
				     20 Hz, aproximadamente. */
	DLPF_10_HZ, /**< Filtro pasa-bajo digital con frecuencia de corte
					 10 Hz, aproximadamente. */
	DLPF_5_HZ   /**< Filtro pasa-bajo digital con frecuencia de corte
					 5 Hz, aproximadamente. */
}MPU6050_Digital_Low_Pass_Filter_t;


/**
  * @brief Rango de trabajo del giroscopio.
  */
typedef enum{
	GYRO_FS_250_DEG_PER_SEC = 0, /**< Escala máxima de 250°/s. */
	GYRO_FS_500_DEG_PER_SEC,	 /**< Escala máxima de 500°/s. */
	GYRO_FS_1000_DEG_PER_SEC,	 /**< Escala máxima de 1000°/s. */
	GYRO_FS_2000_DEG_PER_SEC	 /**< Escala máxima de 2000°/s. */
}MPU6050_Gyroscope_Full_Scale_Range_t;

/**
  * @brief Rango de trabajo del acelerómetro.
  */
typedef enum{
	ACCEL_FS_2G = 0, /**< Escala máxima de 2g. */
	ACCEL_FS_4G,	 /**< Escala máxima de 4g. */
	ACCEL_FS_8G,	 /**< Escala máxima de 8g. */
	ACCEL_FS_16G	 /**< Escala máxima de 16g. */
}MPU6050_Accelerometer_Full_Scale_Range_t;

/**
  * @brief Fuente de reloj para el MPU6050.
  */
typedef enum{
	INTERNAL_8_MHZ_OSCILLATOR = 0, /**< Oscilador interno de 8 MHz. */
	PLL_X_GYRO_REF = 1, /**< PLL con el reloj del eje X del giroscopio. */
	PLL_Y_GYRO_REF = 2, /**< PLL con el reloj del eje Y del giroscopio. */
	PLL_Z_GYRO_REF = 3, /**< PLL con el reloj del eje Z del giroscopio. */
	PLL_EXTERNAL_32P768_KHZ_REF = 4, /**< PLL con un cristal externo de 
	                                      32.768 KHz. */
	PLL_EXTERNAL_19P2_MHZ_REF = 5, /**< PLL con una señal de reloj externa de 
									    192.2 MHz. */
	CLOCK_STOP = 7 /**< Sin señal de reloj (dispositivo detenido). */
}MPU6050_Clock_Source_t;


/**
  * @brief Estructura para configurar el MPU6050.
  */
typedef struct{
	uint8_t sample_rate_divider; /**< Divisor de la frecuencia de muestreo. */
	MPU6050_Clock_Source_t clock_source; /* Fuente de reloj. */
	MPU6050_External_Frame_Synchronization_t external_frame_synchronization; /**< Sincronización externa. */ 												
	MPU6050_Digital_Low_Pass_Filter_t digital_low_pass_filter; /**< Filtro digital. */
	MPU6050_Gyroscope_Full_Scale_Range_t gyro_full_scale_range; /**< Rango de trabajo del giroscopio. */
	MPU6050_Accelerometer_Full_Scale_Range_t accel_full_scale_range; /**< Rango de trabajo del acelerómetro. */
}MPU6050_Config_t;


/* Function declaration */

/**
  * @brief Función para configurar el MPU6050.
  * @param imu_conf Puntero a estructura con los parámetros de configuración.
  * @return Si la configuración se llevó a cabo exitosamente o no.
  * @details Para utilizar esta función, primero se debe crear una estructura 
  * de tipo MPU6050_Config_t, la cual contiene los parámetros de 
  * configuración.\n
  * Si la configuración se realiza de manera exitosa, la función retorna el 
  * valor I2C_OK; de lo contrario, la función retorna I2C_ERROR.\n
  * Ejemplo: 
  * @code
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
  * @endcode
  */
uint8_t MPU6050_Configure(MPU6050_Config_t *imu_conf);

/**
  * @brief Función para medir aceleración con el MPU6050.
  * @return Si la medición se llevó a cabo exitosamente o no.
  * @details Si la medición se realiza de manera exitosa, la función 
  * retorna el valor I2C_OK; de lo contrario, la función retorna 
  * I2C_ERROR.\n
  * Ejemplo: 
  * @code
	uint8_t aux = I2C_OK;
	char mensaje[50];
	
	aux = MPU6050_Read_Accelerometer();
	if(aux == I2C_OK)
	{
		sprintf(mensaje, "Se midió la aceleración.");
	}
	else
	{
		sprintf(mensaje, "No se pudo medir la aceleración.");
	}
  * @endcode
  */
uint8_t MPU6050_Read_Accelerometer(void);

/**
  * @brief Función para medir velocidad angular MPU6050.
  * @return Si la medición se llevó a cabo exitosamente o no.
  * @details Si la medición se realiza de manera exitosa, la función 
  * retorna el valor I2C_OK; de lo contrario, la función retorna 
  * I2C_ERROR.\n
  * Ejemplo: 
  * @code
	uint8_t aux = I2C_OK;
	char mensaje[50];
	
	aux = MPU6050_Read_Gyroscope();
	if(aux == I2C_OK)
	{
		sprintf(mensaje, "Se midió la velocidad angular.");
	}
	else
	{
		sprintf(mensaje, "No se pudo medir la velocidad angular.");
	}
  * @endcode
  */
uint8_t MPU6050_Read_Gyroscope(void);

/**
  * @brief Función para medir temperatura con el MPU6050.
  * @return Si la medición se llevó a cabo exitosamente o no.
  * @details Si la medición se realiza de manera exitosa, la función 
  * retorna el valor I2C_OK; de lo contrario, la función retorna 
  * I2C_ERROR.\n
  * Ejemplo: 
  * @code
	uint8_t aux = I2C_OK;
	char mensaje[50];
	
	aux = MPU6050_Read_Temperature();
	if(aux == I2C_OK)
	{
		sprintf(mensaje, "Se midió la temperatura.");
	}
	else
	{
		sprintf(mensaje, "No se pudo medir la temperatura.");
	}
  * @endcode
  */
uint8_t MPU6050_Read_Temperature(void);

/**
  * @brief Función para medir aceleración, velocidad angular y temperatura 
  * con el MPU6050.
  * @return Si la medición se llevó a cabo exitosamente o no.
  * @details Si la medición se realiza de manera exitosa, la función 
  * retorna el valor I2C_OK; de lo contrario, la función retorna 
  * I2C_ERROR.\n
  * Ejemplo: 
  * @code
	uint8_t aux = I2C_OK;
	char mensaje[50];
	
	aux = MPU6050_Read_All_Sensors();
	if(aux == I2C_OK)
	{
		sprintf(mensaje, "Se realizaron las mediciones.");
	}
	else
	{
		sprintf(mensaje, "No se pudo realizar las mediciones.");
	}
  * @endcode
  */
uint8_t MPU6050_Read_All_Sensors(void);

/**
  * @brief Función para leer el valor de temperatura (en formato binario) 
    medido previamente.
  * @param temp Puntero a la variable donde se almacenará el valor leído.
  * @details Antes de llamar a esta función, es necesario haber medido 
  * la temperatura previamente.\n
  * Ejemplo: 
  * @code
  uint8_t aux = I2C_OK;
  int16_t temp_bin;
  char mensaje[50];
  
  //Primero, medir la temperatura.
  aux = MPU6050_Read_Temperature();
  if(aux == I2C_OK)
  {
	  //Luego, leer la temperatura y almacenarla.
	  MPU6050_Get_Temperature_Output(&temp_bin); 
  }
  else
  {
	  sprintf(mensaje, "No se pudo leer la temperatura.");
  }
  * @endcode
  */
void MPU6050_Get_Temperature_Output(int16_t *temp);

/**
  * @brief Función para leer las componentes de la aceleración 
    (en formato binario) medidas previamente.
  * @param accel_x Puntero a la variable donde se almacenará la componente ax.
  * @param accel_y Puntero a la variable donde se almacenará la componente ay.
  * @param accel_z Puntero a la variable donde se almacenará la componente az.
  * @details Antes de llamar a esta función, es necesario haber medido las 
  * componentes de la aceleración previamente.\n
  * Ejemplo: 
  * @code
  uint8_t aux = I2C_OK;
  int16_t ax_bin, ay_bin, az_bin;
  char mensaje[50];
  
  //Primero, medir las componentes de la aceleración.
  aux = MPU6050_Read_Accelerometer();
  if(aux == I2C_OK)
  {
	  //Luego, leer las componentes de aceleración y almacenarlas.
	  MPU6050_Get_Accelerometer_Output(&ax_bin, &ay_bin, &az_bin); 
  }
  else
  {
	  sprintf(mensaje, "No se pudo leer la aceleración.");
  }
  * @endcode
  */
void MPU6050_Get_Accelerometer_Output(int16_t *accel_x, int16_t *accel_y, int16_t *accel_z);

/**
  * @brief Función para leer las componentes de la velocidad angular 
  * (en formato binario) medidas previamente.
  * @param gyro_x Puntero a la variable donde se almacenará la componente wx.
  * @param gyro_y Puntero a la variable donde se almacenará la componente wy.
  * @param gyro_z Puntero a la variable donde se almacenará la componente wz.
  * @details Antes de llamar a esta función, es necesario haber medido las 
  * componentes de la velocidad angular previamente.\n
  * Ejemplo: 
  * @code
  uint8_t aux = I2C_OK;
  int16_t wx_bin, wy_bin, wz_bin;
  char mensaje[50];
  
  //Primero, medir las componentes de la velocidad angular.
  aux = MPU6050_Read_Gyroscope();
  if(aux == I2C_OK)
  {
	  //Luego, leer las componentes de la velocidad angular y almacenarlas.
	  MPU6050_Get_Gyroscope_Output(&wx_bin, &wy_bin, &wz_bin); 
  }
  else
  {
	  sprintf(mensaje, "No se pudo leer la velocidad angular.");
  }
  * @endcode
  */
void MPU6050_Get_Gyroscope_Output(int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z);

/**
  * @brief Función para leer el valor de temperatura (en grados Celsius) 
    medido previamente.
  * @param temp Puntero a la variable donde se almacenará el valor leído.
  * @details Antes de llamar a esta función, es necesario haber medido 
  * la temperatura previamente.\n
  * Ejemplo: 
  * @code
  uint8_t aux = I2C_OK;
  float temp_celsius;
  char mensaje[50];
  
  //Primero, medir la temperatura.
  aux = MPU6050_Read_Temperature();
  if(aux == I2C_OK)
  {
	  //Luego, leer la temperatura y almacenarla.
	  MPU6050_Get_Temperature_Deg_Celsius(&temp_celsius); 
  }
  else
  {
	  sprintf(mensaje, "No se pudo leer la temperatura.");
  }
  * @endcode
  */
void MPU6050_Get_Temperature_Deg_Celsius(float *temp);

/**
  * @brief Función para leer las componentes de la aceleración 
    (expresadas en g) medidas previamente.
  * @param accel_x Puntero a la variable donde se almacenará la componente ax.
  * @param accel_y Puntero a la variable donde se almacenará la componente ay.
  * @param accel_z Puntero a la variable donde se almacenará la componente az.
  * @details Antes de llamar a esta función, es necesario haber medido las 
  * componentes de la aceleración previamente.\n
  * Ejemplo: 
  * @code
  uint8_t aux = I2C_OK;
  int16_t ax_g, ay_g, az_g;
  char mensaje[50];
  
  //Primero, medir las componentes de la aceleración.
  aux = MPU6050_Read_Accelerometer();
  if(aux == I2C_OK)
  {
	  //Luego, leer las componentes de aceleración y almacenarlas.
	  MPU6050_Get_Acceleration_G(&ax_g, &ay_g, &az_g); 
  }
  else
  {
	  sprintf(mensaje, "No se pudo leer la aceleración.");
  }
  * @endcode
  */
void MPU6050_Get_Acceleration_G(float *accel_x, float *accel_y, float *accel_z);

/**
  * @brief Función para leer las componentes de la aceleración 
    (expresadas en m/s2) medidas previamente.
  * @param accel_x Puntero a la variable donde se almacenará la componente ax.
  * @param accel_y Puntero a la variable donde se almacenará la componente ay.
  * @param accel_z Puntero a la variable donde se almacenará la componente az.
  * @details Antes de llamar a esta función, es necesario haber medido las 
  * componentes de la aceleración previamente.\n
  * Ejemplo: 
  * @code
  uint8_t aux = I2C_OK;
  int16_t ax_m_s2, ay_m_s2, az_m_s2;
  char mensaje[50];
  
  //Primero, medir las componentes de la aceleración.
  aux = MPU6050_Read_Accelerometer();
  if(aux == I2C_OK)
  {
	  //Luego, leer las componentes de aceleración y almacenarlas.
	  MPU6050_Get_Acceleration_Meter_Per_Sec2(&ax_m_s2, &ay_m_s2, &az_m_s2); 
  }
  else
  {
	  sprintf(mensaje, "No se pudo leer la aceleración.");
  }
  * @endcode
  */
void MPU6050_Get_Acceleration_Meter_Per_Sec2(float *accel_x, float *accel_y, float *accel_z);

/**
  * @brief Función para leer las componentes de la velocidad angular 
  * (expresadas en rad/s) medidas previamente.
  * @param gyro_x Puntero a la variable donde se almacenará la componente wx.
  * @param gyro_y Puntero a la variable donde se almacenará la componente wy.
  * @param gyro_z Puntero a la variable donde se almacenará la componente wz.
  * @details Antes de llamar a esta función, es necesario haber medido las 
  * componentes de la velocidad angular previamente.\n
  * Ejemplo: 
  * @code
  uint8_t aux = I2C_OK;
  int16_t wx_rad_s, wy_rad_s, wz_rad_s;
  char mensaje[50];
  
  //Primero, medir las componentes de la velocidad angular.
  aux = MPU6050_Read_Gyroscope();
  if(aux == I2C_OK)
  {
	  //Luego, leer las componentes de velocidad angular y almacenarlas.
	  MPU6050_Get_Angular_Velocity_Deg_Per_Sec(&wx_rad_s, &wy_rad_s, &wz_rad_s); 
  }
  else
  {
	  sprintf(mensaje, "No se pudo leer la velocidad angular.");
  }
  * @endcode
  */
void MPU6050_Get_Angular_Velocity_Deg_Per_Sec(float *gyro_x, float *gyro_y, float *gyro_z);

#endif /* MT_MPU6050_H_ */