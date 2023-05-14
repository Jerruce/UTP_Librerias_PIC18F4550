/* 
 * File:   MT_adc.h
 * Author: mtorres
 *
 * Created on 1 de octubre de 2022, 05:48 AM
 */

#ifndef MT_ADC_H
#define	MT_ADC_H

/* Inclusión de archivos */
#include <xc.h>
#include <stdint.h>


/* Definición de tipos */

typedef enum
{
    PBADEN_OFF = 0,
    PBADEN_ON        
}
adc_pbaden_status_t;


typedef enum
{
    ADC_DISABLED = 0,
    ADC_ENABLED
}
adc_status_t;


typedef enum
{
    ADC_CHANNEL_0 = 0,
    ADC_CHANNEL_1,
    ADC_CHANNEL_2,
    ADC_CHANNEL_3,
    ADC_CHANNEL_4,
    ADC_CHANNEL_5,
    ADC_CHANNEL_6,
    ADC_CHANNEL_7,
    ADC_CHANNEL_8,
    ADC_CHANNEL_9,
    ADC_CHANNEL_10,
    ADC_CHANNEL_11,
    ADC_CHANNEL_12        
}
adc_channel_t;


typedef enum
{
    ADC_12_CHANNELS_ENABLED = 2,
    ADC_11_CHANNELS_ENABLED,
    ADC_10_CHANNELS_ENABLED,
    ADC_9_CHANNELS_ENABLED,
    ADC_8_CHANNELS_ENABLED,
    ADC_7_CHANNELS_ENABLED,
    ADC_6_CHANNELS_ENABLED,
    ADC_5_CHANNELS_ENABLED,
    ADC_4_CHANNELS_ENABLED,
    ADC_3_CHANNELS_ENABLED,
    ADC_2_CHANNELS_ENABLED,
    ADC_1_CHANNEL_ENABLED,
    ADC_ALL_CHANNELS_DISABLED        
}
adc_channels_enabled_t;


typedef enum
{
    ADC_VREF_VCC = 0,
    ADC_VREF_POS_EXT,
    ADC_VREF_NEG_EXT,
    ADC_VREF_POS_AND_NEG_EXT        
}
adc_voltage_ref_config_t;


typedef enum
{
    ADC_LEFT_JUSTIFIED = 0,
    ADC_RIGHT_JUSTIFIED        
}
adc_format_t;


typedef enum
{
    ADC_CLK_FOSC_2 = 0,
    ADC_CLK_FOSC_8,
    ADC_CLK_FOSC_32,
    ADC_CLK_FRC,
    ADC_CLK_FOSC_4,
    ADC_CLK_FOSC_16,
    ADC_CLK_FOSC_64        
}
adc_clock_source_t;


typedef enum
{
    ADC_ACQ_TIME_0_TAD = 0,
    ADC_ACQ_TIME_2_TAD,
    ADC_ACQ_TIME_4_TAD,
    ADC_ACQ_TIME_6_TAD,
    ADC_ACQ_TIME_8_TAD,
    ADC_ACQ_TIME_12_TAD,
    ADC_ACQ_TIME_16_TAD,
    ADC_ACQ_TIME_20_TAD        
}
adc_acquisition_time_t;


typedef enum
{
    ADC_INTERRUPT_DISABLED = 0,
    ADC_INTERRUPT_ENABLED        
}
adc_interrupt_status_t;


typedef struct
{
    adc_status_t adc_status;
    adc_pbaden_status_t pbaden_status;
    adc_voltage_ref_config_t voltage_reference;
    adc_clock_source_t clock_source;
    adc_acquisition_time_t acq_time;
    adc_format_t data_format;
    adc_channels_enabled_t channels_enabled;
    adc_interrupt_status_t adc_interrupt;
}
adc_t;


/* Declaración de funciones */
void ADC_Configure(adc_t *adc_param);
void ADC_Start_Conversion(void);
uint8_t ADC_Check_Conversion_Status(void);
void ADC_Channel_Select(adc_channel_t adc_ch);
uint16_t ADC_Read_10_Bits(void);
uint8_t ADC_Read_8_Bits(void);

#endif	/* MT_ADC_H */






