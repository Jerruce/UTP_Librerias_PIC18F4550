
/* Inclusión de archivos */
#include "MT_adc.h"

/* Definición de funciones */
void ADC_Configure(adc_t *adc_param)
{  
  ADCON0bits.ADON = adc_param->adc_status & 0x01;
  ADCON1bits.VCFG = adc_param->voltage_reference & 0x03;
  
  if(adc_param->channels_enabled == ADC_12_CHANNELS_ENABLED )
  {
      if(adc_param->pbaden_status == 1)
      {
          ADCON1bits.PCFG = 0;
      }
      else
      {
          ADCON1bits.PCFG = 7;
      }
  }
  else
  {
      ADCON1bits.PCFG = adc_param->channels_enabled & 0x0F; 
  }
  
  ADCON2bits.ADFM = adc_param->data_format & 1;
  ADCON2bits.ACQT = adc_param->acq_time & 0x03;
  ADCON2bits.ADCS = adc_param->clock_source & 0x03;
  PIE1bits.ADIE = adc_param->adc_interrupt & 0x01;
  
}


void ADC_Start_Conversion(void)
{
    ADCON0bits.GO_DONE = 1;
}


uint8_t ADC_Check_Conversion_Status(void)
{
    return ADCON0bits.GO_DONE;
}


void ADC_Channel_Select(adc_channel_t adc_ch)
{
    ADCON0bits.CHS = adc_ch & 0x0F;
}


uint16_t ADC_Read_10_Bits(void)
{
    uint16_t adc_value = 0;
    
    adc_value = (ADRESH << 8) | ADRESL;
    return adc_value;
}


uint8_t ADC_Read_8_Bits(void)
{
    uint8_t adc_value = 0;
    
    adc_value = ADRESH;
    return adc_value;
}