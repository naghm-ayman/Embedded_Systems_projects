/* 
 * File:   hal_adc.c
 * Author: Naghm Ayman Omar
 *
 * Created on 18 July 2024, 16:15
 */

#include"hal_adc.h"

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*ADC_InterruptHandler)(void) = NULL;
#endif

static inline void adc_input_channel_port_config(adc_channel_select_t channel);
static inline void select_result_format(const adc_config_t *_adc);
static inline void configure_voltage_reference(const adc_config_t *_adc);

Std_ReturnType ADC_Init(const adc_config_t *_adc){
     Std_ReturnType ret = E_OK;
     
     if(NULL== _adc){
         ret= E_NOK;
     }
     else{
       /* Disable the ADC*/
         ADC_CONVERTER_DISABLE();
       /* Configure the Acquisition time*/
         ADCON2bits.ACQT = _adc->acquisition_time;
       /* Configure the Conversion clock*/
          ADCON2bits.ADCS = _adc->conversion_time;
       /* Configure the Default channel */
          ADCON0bits.CHS = _adc->channel_select;
          adc_input_channel_port_config(_adc->channel_select);
       /*Configure the Interrupt */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
          ADC_InterruptEnable();
          ADC_InterruptFlagClear();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
          if(Interrupt_High_Priority == _adc->priority){
              ADC_HighPrioritySet();
          }
          else if(Interrupt_Low_Priority == _adc->priority){
              ADC_LowPrioritySet();
          }
          else{
              
          }
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
          ADC_InterruptHandler = _adc->ADC_InterruptHandler;
#endif
       /* Configure the Result format */
          select_result_format(_adc);
       /* Configure the Voltage reference */
          configure_voltage_reference(_adc);
       /* Enable the ADC*/
         ADC_CONVERTER_ENABLE();
     }
     return(ret);
}
Std_ReturnType ADC_DeInit(const adc_config_t *_adc){
    Std_ReturnType ret = E_OK;
     
     if(NULL== _adc){
         ret= E_NOK;
     }
     else{
       /* Disable the ADC*/
         ADC_CONVERTER_DISABLE();
       /*Disable the Interrupt */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
       ADC_InterruptDisable();
#endif
     }
     return(ret);
}
Std_ReturnType ADC_SelectChannel(const adc_config_t *_adc, adc_channel_select_t channel){
    Std_ReturnType ret = E_OK;
     
     if(NULL== _adc){
         ret= E_NOK;
     }
     else{
       /* Configure the Default channel */
          ADCON0bits.CHS = channel;
          adc_input_channel_port_config(channel);
     }
     return(ret);
}
Std_ReturnType ADC_StartConversion(const adc_config_t *_adc){
    Std_ReturnType ret = E_OK;
     
     if(NULL == _adc){
         ret= E_NOK;
     }
     else{
       ADC_START_CONVERSION();
     }
     return(ret);
}
Std_ReturnType ADC_IsConversionDone(const adc_config_t *_adc, uint8 *conversion_st){
    Std_ReturnType ret = E_OK;
     
     if( (NULL == _adc) || (NULL == conversion_st)){
         ret= E_NOK;
     }
     else{
       *conversion_st = (uint8)(!(ADC_CONVERSION_STATUS())); //put the value ADCON0bits.GO_nDONE if the logic is wrong
     }
     return(ret);
}
Std_ReturnType ADC_GetConversionResult(const adc_config_t *_adc, adc_result_t *conversion_st){
    Std_ReturnType ret = E_OK;
     
     if( (NULL == _adc) || (NULL == conversion_st)){
         ret= E_NOK;
     }
     else {
        if (ADC_RESULT_RIGHT == _adc->result_format) {
            *conversion_st = (adc_result_t)((ADRESH << 8) + ADRESL);
        } else if (ADC_RESULT_LEFT == _adc->result_format) {
           *conversion_st = (adc_result_t)(((ADRESH << 8) + ADRESL) >> 6);

        } else {
            *conversion_st = (adc_result_t)((ADRESH << 8) + ADRESL);
        }
     }
     return(ret);
}
Std_ReturnType ADC_GetConversion_Blocking(const adc_config_t *_adc, adc_channel_select_t channel ,adc_result_t *conversion_st){
    Std_ReturnType ret = E_OK;
     
     if( (NULL == _adc) || (NULL == conversion_st)){
         ret= E_NOK;
     }
     else{
       /* select the A/D channel */
         ret = ADC_SelectChannel(_adc, channel);
       /* start the conversion */
         ret = ADC_StartConversion(_adc);
       /* check if conversion is completed */ 
         while(ADC_CONVERSION_STATUS());  //put the value ADCON0bits.GO_nDONE if ant logic is wrong
         ret = ADC_GetConversionResult(_adc, conversion_st);
     }
     return(ret);
}
Std_ReturnType ADC_StartConversion_Interrupt(const adc_config_t *_adc, adc_channel_select_t channel){
    Std_ReturnType ret = E_OK;
     
     if(NULL == _adc){
         ret= E_NOK;
     }
     else{
       /* select the A/D channel */
         ret = ADC_SelectChannel(_adc, channel);
       /* start the conversion */
         ret = ADC_StartConversion(_adc);      
     }
     return(ret);
}
 

static inline void adc_input_channel_port_config(adc_channel_select_t channel){
    switch(channel){
        case ADC_CHANNEL_AN0: SET_BIT(TRISA, _TRISA_RA0_POSN);
            break;
        case ADC_CHANNEL_AN1: SET_BIT(TRISA, _TRISA_RA1_POSN);
            break;
        case ADC_CHANNEL_AN2: SET_BIT(TRISA, _TRISA_RA2_POSN);
            break;
        case ADC_CHANNEL_AN3: SET_BIT(TRISA, _TRISA_RA3_POSN);
            break;
        case ADC_CHANNEL_AN4: SET_BIT(TRISA, _TRISA_RA5_POSN);
            break;
        case ADC_CHANNEL_AN5: SET_BIT(TRISE, _TRISE_RE0_POSN);
            break;
        case ADC_CHANNEL_AN6: SET_BIT(TRISE, _TRISE_RE1_POSN);
            break;
        case ADC_CHANNEL_AN7: SET_BIT(TRISE, _TRISE_RE2_POSN);
            break;
        case ADC_CHANNEL_AN8: SET_BIT(TRISB, _TRISB_RB2_POSN);
            break;
        case ADC_CHANNEL_AN9: SET_BIT(TRISB, _TRISB_RB3_POSN);
            break;
        case ADC_CHANNEL_AN10: SET_BIT(TRISB, _TRISB_RB1_POSN);
            break;
        case ADC_CHANNEL_AN11: SET_BIT(TRISB, _TRISB_RB4_POSN);
            break;
        case ADC_CHANNEL_AN12: SET_BIT(TRISB, _TRISB_RB0_POSN);
            break;
        
    }
    
}
static inline void select_result_format(const adc_config_t *_adc){
    if(ADC_RESULT_RIGHT == _adc->result_format){
        ADC_RESULT_RIGHT_FORMAT();
    }
    else if(ADC_RESULT_LEFT == _adc->result_format){
        ADC_RESULT_LEFT_FORMAT();

    }
    else{
       ADC_RESULT_RIGHT_FORMAT();

    }
}
static inline void configure_voltage_reference(const adc_config_t *_adc){
    if(ADC_VOLTAGE_REFRENCE_ENABLE == _adc->voltage_refrence){
        ADC_ENABLE_VOLTAGE_REFRENCE();
    }
    else if(ADC_VOLTAGE_REFRENCE_DISABLE == _adc->voltage_refrence){
        ADC_DISABLE_VOLTAGE_REFRENCE();

    }
    else{
       ADC_DISABLE_VOLTAGE_REFRENCE();

    }
}
void ADC_ISR(void){
    ADC_InterruptFlagClear();
    if(ADC_InterruptHandler){
        ADC_InterruptHandler();
        
    }
}

