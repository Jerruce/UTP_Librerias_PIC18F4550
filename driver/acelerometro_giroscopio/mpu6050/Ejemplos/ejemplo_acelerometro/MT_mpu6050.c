/**
  * @file MT_mpu6050.c	
  * @version 1.0
  * @date 05/04/2022
  * @author Miguel Torres
  * @brief  Archivo fuente con la implementación de funciones para el manejo 
  * del IMU MPU6050. 	
  */

/* Inclusión de archivos */
#include "MT_mpu6050.h"

/* Definición de variables */

static int16_t accel_x_out = 0, accel_y_out = 0, accel_z_out = 0;
static int16_t gyro_x_out = 0, gyro_y_out = 0, gyro_z_out = 0;
static int16_t temp_out = 0;

static float ax_m_s2 = 0, ay_m_s2 = 0, az_m_s2 = 0;
static float wx_deg_s = 0, wy_deg_s = 0, wz_deg_s = 0;
static float temp_celsius = 0;

static float accel_sensitivity = ACCEL_SENSITIVITY_FS_16G;
static float gyro_sensitivity = GYRO_SENSITIVITY_FS_2000_DEG_S;

static uint8_t mpu6050_i2c_write_buffer[MPU6050_I2C_WRITE_BUFF_SIZE];
static uint8_t mpu6050_i2c_read_buffer[MPU6050_I2C_READ_BUFF_SIZE];

/* Definición de funciones */

uint8_t MPU6050_Configure(MPU6050_Config_t *imu_conf){
	
	uint8_t i2c_status = I2C_OK;
	uint8_t sample_rate_div = 0;
	uint8_t config = 0;
	uint8_t gyro_config = 0;
	uint8_t accel_config = 0;
	uint8_t power_management_1 = 0;
	
	switch(imu_conf->accel_full_scale_range){
		
		case ACCEL_FS_2G:
		accel_sensitivity = ACCEL_SENSITIVITY_FS_2G;
		break;
		
		case ACCEL_FS_4G:
		accel_sensitivity = ACCEL_SENSITIVITY_FS_4G;
		break;
		
		case ACCEL_FS_8G:
		accel_sensitivity = ACCEL_SENSITIVITY_FS_8G;
		break;
		
		case ACCEL_FS_16G:
		accel_sensitivity = ACCEL_SENSITIVITY_FS_16G;
		break;
		
		default:
		break;
		
	}
	

	switch(imu_conf->accel_full_scale_range){
		
		case ACCEL_FS_2G:
		gyro_sensitivity = GYRO_SENSITIVITY_FS_250_DEG_S;
		break;
		
		case ACCEL_FS_4G:
		gyro_sensitivity = GYRO_SENSITIVITY_FS_500_DEG_S;
		break;
		
		case ACCEL_FS_8G:
		gyro_sensitivity = GYRO_SENSITIVITY_FS_1000_DEG_S;
		break;
		
		case ACCEL_FS_16G:
		gyro_sensitivity = GYRO_SENSITIVITY_FS_2000_DEG_S;
		break;
		
		default:
		break;
		
	}
	
	
	sample_rate_div = imu_conf->sample_rate_divider;
	config = ((imu_conf->external_frame_synchronization & 0x07) << BIT_EXT_SYNC_SET_0) | (imu_conf->digital_low_pass_filter & 0x07);
	gyro_config = (imu_conf->gyro_full_scale_range & 0x03) << BIT_FS_SEL_0;
	accel_config = (imu_conf->accel_full_scale_range & 0x03) << BIT_AFS_SEL_0;
	power_management_1 = imu_conf->clock_source & 0x07;
	
	mpu6050_i2c_write_buffer[0] = MPU6050_PWR_MGMT_1;
	mpu6050_i2c_write_buffer[1] = power_management_1;
	i2c_status = I2Cn_Master_Write_Data(MPU6050_I2C_MODULE, MPU6050_I2C_SLAVE_ADDRESS, 2, mpu6050_i2c_write_buffer);
	
	if(i2c_status == I2C_OK){
		
		mpu6050_i2c_write_buffer[0] = MPU6050_SMPLRT_DIV;
		mpu6050_i2c_write_buffer[1] = sample_rate_div;
		i2c_status = I2Cn_Master_Write_Data(MPU6050_I2C_MODULE, MPU6050_I2C_SLAVE_ADDRESS, 2, mpu6050_i2c_write_buffer);

		if(i2c_status == I2C_OK){
			
			mpu6050_i2c_write_buffer[0] = MPU6050_CONFIG;
			mpu6050_i2c_write_buffer[1] = config;
			i2c_status = I2Cn_Master_Write_Data(MPU6050_I2C_MODULE, MPU6050_I2C_SLAVE_ADDRESS, 2, mpu6050_i2c_write_buffer);

			if(i2c_status == I2C_OK){
				
				mpu6050_i2c_write_buffer[0] = MPU6050_GYRO_CONFIG;
				mpu6050_i2c_write_buffer[1] = gyro_config;
				i2c_status = I2Cn_Master_Write_Data(MPU6050_I2C_MODULE, MPU6050_I2C_SLAVE_ADDRESS, 2, mpu6050_i2c_write_buffer);
				
				if(i2c_status == I2C_OK){
					
					mpu6050_i2c_write_buffer[0] = MPU6050_ACCEL_CONFIG;
					mpu6050_i2c_write_buffer[1] = accel_config;
					i2c_status = I2Cn_Master_Write_Data(MPU6050_I2C_MODULE, MPU6050_I2C_SLAVE_ADDRESS, 2, mpu6050_i2c_write_buffer);
					
					}else{
					//Does nothing
				}
				
				}else{
				//Does nothing
			}

			}else{
			//Does nothing
		}
		
		}else{
		//Does nothing
	}
	
	return i2c_status;
}


uint8_t MPU6050_Read_Accelerometer(void){
	
	uint8_t i2c_status = I2C_OK;
	
	mpu6050_i2c_write_buffer[0] = MPU6050_ACCEL_XOUT_H;
	i2c_status = I2Cn_Master_Write_Data(MPU6050_I2C_MODULE, MPU6050_I2C_SLAVE_ADDRESS, 1, mpu6050_i2c_write_buffer);
	
	if(i2c_status == I2C_OK){
		
		i2c_status = I2Cn_Master_Read_Data(MPU6050_I2C_MODULE, MPU6050_I2C_SLAVE_ADDRESS, 6, mpu6050_i2c_read_buffer);
		
		if(i2c_status == I2C_OK){
			
			accel_x_out = (((int16_t)mpu6050_i2c_read_buffer[0]) << 8) | mpu6050_i2c_read_buffer[1];
			accel_y_out = (((int16_t)mpu6050_i2c_read_buffer[2]) << 8) | mpu6050_i2c_read_buffer[3];
			accel_z_out = (((int16_t)mpu6050_i2c_read_buffer[4]) << 8) | mpu6050_i2c_read_buffer[5];
			
		}else{
			//Does nothing
		}
		
	}else{
		//Does nothing
	}
	
	return i2c_status;
	
}


uint8_t MPU6050_Read_Gyroscope(void){

	uint8_t i2c_status = I2C_OK;

	mpu6050_i2c_write_buffer[0] = MPU6050_GYRO_XOUT_H;
	i2c_status = I2Cn_Master_Write_Data(MPU6050_I2C_MODULE, MPU6050_I2C_SLAVE_ADDRESS, 1, mpu6050_i2c_write_buffer);

	if(i2c_status == I2C_OK){
		
		i2c_status = I2Cn_Master_Read_Data(MPU6050_I2C_MODULE, MPU6050_I2C_SLAVE_ADDRESS, 6, mpu6050_i2c_read_buffer);
		
		if(i2c_status == I2C_OK){
			
			gyro_x_out = (((int16_t)mpu6050_i2c_read_buffer[0]) << 8) | mpu6050_i2c_read_buffer[1];
			gyro_y_out = (((int16_t)mpu6050_i2c_read_buffer[2]) << 8) | mpu6050_i2c_read_buffer[3];
			gyro_z_out = (((int16_t)mpu6050_i2c_read_buffer[4]) << 8) | mpu6050_i2c_read_buffer[5];
			
			}else{
			//Does nothing
		}
		
		}else{
		//Does nothing
	}

	return i2c_status;
	
}


uint8_t MPU6050_Read_Temperature(void){

	uint8_t i2c_status = I2C_OK;

	mpu6050_i2c_write_buffer[0] = MPU6050_TEMP_OUT_H;
	i2c_status = I2Cn_Master_Write_Data(MPU6050_I2C_MODULE, MPU6050_I2C_SLAVE_ADDRESS, 1, mpu6050_i2c_write_buffer);

	if(i2c_status == I2C_OK){
		
		i2c_status = I2Cn_Master_Read_Data(MPU6050_I2C_MODULE, MPU6050_I2C_SLAVE_ADDRESS, 2, mpu6050_i2c_read_buffer);
		
		if(i2c_status == I2C_OK){
			
			temp_out = (((int16_t)mpu6050_i2c_read_buffer[0]) << 8) | mpu6050_i2c_read_buffer[1];
			
			}else{
			//Does nothing
		}
		
		
		}else{
		//Does nothing
	}

	return i2c_status;
	
}


uint8_t MPU6050_Read_All_Sensors(void){

	uint8_t i2c_status = I2C_OK;

	mpu6050_i2c_write_buffer[0] = MPU6050_ACCEL_XOUT_H;
	i2c_status = I2Cn_Master_Write_Data(MPU6050_I2C_MODULE, MPU6050_I2C_SLAVE_ADDRESS, 1, mpu6050_i2c_write_buffer);

	if(i2c_status == I2C_OK){
		
		i2c_status = I2Cn_Master_Read_Data(MPU6050_I2C_MODULE, MPU6050_I2C_SLAVE_ADDRESS, 14, mpu6050_i2c_read_buffer);
		
		if(i2c_status == I2C_OK){
			
			accel_x_out = (((int16_t)mpu6050_i2c_read_buffer[0]) << 8) | mpu6050_i2c_read_buffer[1];
			accel_y_out = (((int16_t)mpu6050_i2c_read_buffer[2]) << 8) | mpu6050_i2c_read_buffer[3];
			accel_z_out = (((int16_t)mpu6050_i2c_read_buffer[4]) << 8) | mpu6050_i2c_read_buffer[5];
			temp_out = (((int16_t)mpu6050_i2c_read_buffer[6]) << 8) | mpu6050_i2c_read_buffer[7];
			gyro_x_out = (((int16_t)mpu6050_i2c_read_buffer[8]) << 8) | mpu6050_i2c_read_buffer[9];
			gyro_y_out = (((int16_t)mpu6050_i2c_read_buffer[10]) << 8) | mpu6050_i2c_read_buffer[11];
			gyro_z_out = (((int16_t)mpu6050_i2c_read_buffer[12]) << 8) | mpu6050_i2c_read_buffer[13];
			
			}else{
			//Does nothing
		}
		
		}else{
		//Does nothing
	}

	return i2c_status;
	
}


void MPU6050_Get_Temperature_Output(int16_t *temp){
	*temp = temp_out;
}


void MPU6050_Get_Accelerometer_Output(int16_t *accel_x, int16_t *accel_y, int16_t *accel_z)
{
	*accel_x = accel_x_out;
	*accel_y = accel_y_out;
	*accel_z = accel_z_out;
}


void MPU6050_Get_Gyroscope_Output(int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z)
{
	*gyro_x = gyro_x_out;
	*gyro_y = gyro_y_out;
	*gyro_z = gyro_z_out;
}


void MPU6050_Get_Temperature_Deg_Celsius(float *temp)
{
	temp_celsius = ((float)(temp_out + TEMPERATURE_OFFSET)) / TEMPERATURE_SENSITIVITY;
	*temp = temp_celsius;
}


void MPU6050_Get_Acceleration_G(float *accel_x, float *accel_y, float *accel_z){
	
	ax_m_s2 = ((float)accel_x_out) / accel_sensitivity;
	ay_m_s2 = ((float)accel_y_out) / accel_sensitivity;
	az_m_s2 = ((float)accel_z_out) / accel_sensitivity;
	
	*accel_x = ax_m_s2;
	*accel_y = ay_m_s2;
	*accel_z = az_m_s2;
}


void MPU6050_Get_Acceleration_Meter_Per_Sec2(float *accel_x, float *accel_y, float *accel_z){
	
	ax_m_s2 = ((float)accel_x_out * GRAVITY_ACCEL_M_PER_S2) / accel_sensitivity;
	ay_m_s2 = ((float)accel_y_out* GRAVITY_ACCEL_M_PER_S2) / accel_sensitivity;
	az_m_s2 = ((float)accel_z_out * GRAVITY_ACCEL_M_PER_S2) / accel_sensitivity;
	
	*accel_x = ax_m_s2;
	*accel_y = ay_m_s2;
	*accel_z = az_m_s2;
}


void MPU6050_Get_Angular_Velocity_Deg_Per_Sec(float *gyro_x, float *gyro_y, float *gyro_z){

	wx_deg_s = ((float)gyro_x_out) / gyro_sensitivity;
	wy_deg_s = ((float)gyro_y_out) / gyro_sensitivity;
	wz_deg_s = ((float)gyro_z_out) / gyro_sensitivity;
	
	*gyro_x = wx_deg_s;
	*gyro_y = wy_deg_s;
	*gyro_z = wz_deg_s;
	
}