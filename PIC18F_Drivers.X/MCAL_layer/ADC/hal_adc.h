/* 
 * File:   hal_adc.h
 * Author: Naghm Ayman Omar
 *
 * Created on 18 July 2024, 16:15
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/*section of INCLUDES */
#include"pic18f4620.h"
#include"../mcal_std_types.h"
#include"../../MCAL_layer/GPIO/hal_gpio.h"
#include"../../MCAL_layer/Interrupt/mcal_internal_interrupt.h"
#include"hal_adc_cfg.h"

/*section of MACRO DECLARATIONS */
#define ADC_AN0_ANALOG_FUNCTIONALITY  0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY  0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY  0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY  0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY  0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY  0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY  0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY  0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY  0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY  0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY 0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY 0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY 0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY  0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY 0x0F

#define ADC_RESULT_RIGHT    0x01U
#define ADC_RESULT_LEFT     0x00U

#define ADC_VOLTAGE_REFRENCE_ENABLE   0x01U
#define ADC_VOLTAGE_REFRENCE_DISABLE  0x00U

#define ADC_CONVERSION_COMPLETED   0x01U
#define ADC_CONVERSION_INPROGRESS  0x00U


/* A/D CONVERSION STATUS : A/D CONVERSION IN PROGRESS / A/D IDLE */
#define ADC_CONVERSION_STATUS()     (ADCON0bits.GO_nDONE)
/* TO DECLARE THAT THE CONVERSION STARTED */
#define ADC_START_CONVERSION()     (ADCON0bits.GO_nDONE = 1)

/* ANALOG TO DIGITAL CONTROL : 
 *  ADC_CONVERTER_ENABLE --> ENABLE THE ANALOG TO DIGITAL
 *  ADC_CONVERTER_DISABLE --> DISABLE THE ANALOG TO DIGITAL 
 */

#define ADC_CONVERTER_ENABLE()     (ADCON0bits.ADON = 1)
#define ADC_CONVERTER_DISABLE()    (ADCON0bits.ADON = 0)

/* VOLTAGE REFERENCE CONFIGRATIONS : 
 *  ADC_ENABLE_VOLTAGE_REFRENCE  --> VOLTAGE REFERENCE IS VREF- &VREF+
 *  ADC_DISABLE_VOLTAGE_REFRENCE --> VOLTAGE REFERENCE IS VDD &VSS 
 */
#define ADC_ENABLE_VOLTAGE_REFRENCE()     do{ADCON1bits.VCFG1 = 1;\
                                             ADCON1bits.VCFG0 = 1;\
                                            }while(0)
#define ADC_DISABLE_VOLTAGE_REFRENCE()     do{ADCON1bits.VCFG1 = 0;\
                                              ADCON1bits.VCFG0 = 0;\
                                             }while(0)

#define ADC_CONVERTER_DISABLE()    (ADCON0bits.ADON = 0)

/* ANALOG TO DIGITAL PORT CONTROL :
 * EX:  ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN4_ANALOG_FUNCTIONALITY) 
 *     "this means that AN4 AN3 AN2 AN1 AN0 are Analog functionality."
 */
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG)  (ADCON1bits.PCFG = _CONFIG)

/* A/D RESULT FORMAT RIGHT /LEFT JUSTIFIED SELECT */
#define ADC_RESULT_RIGHT_FORMAT()   (ADCON2bits.ADFM = 1)
#define ADC_RESULT_LEFT_FORMAT()    (ADCON2bits.ADFM = 0)
/*section of MACRO FUNCTIONS DECLARATIONS */

/*section of DATA TYPE DECLARATIONS*/

typedef enum{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,        
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,        
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,        
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12       
}adc_channel_select_t;

/* ADC Acquisition time 'sampling time ' is the time needed for the ADC to capture
 *  the input voltage during sampling.
 * ADC Acquisition time in Successive Approximation time register (SAR) is the
 *  time needed for the capacitor to charge.
 */
typedef enum{
    ADC_0_TAD = 0,
    ADC_2_TAD, 
    ADC_4_TAD,
    ADC_6_TAD, 
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD, 
}adc_acquisition_time_t;

/* IF the A/D clock source is selected, a delay of one TYC (instruction cycle)
 * is added before the A/D clock starts.
 * This allow the sleep instruction to be executed before starting conversion.
 */
typedef enum{
    ADC_CONVERSION_CLOCK_FOCS_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOCS_DIV_8,
    ADC_CONVERSION_CLOCK_FOCS_DIV_32,
    ADC_CONVERSION_CLOCK_FOCS_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOCS_DIV_4,
    ADC_CONVERSION_CLOCK_FOCS_DIV_16,
    ADC_CONVERSION_CLOCK_FOCS_DIV_64,
}adc_conversion_time_t;

typedef struct{
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(* ADC_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    adc_acquisition_time_t acquisition_time;
    adc_conversion_time_t  conversion_time;
    adc_channel_select_t  channel_select;
    uint8 voltage_refrence : 1;
    uint8 result_format : 1;
    uint8 adc_reserved : 6;
}adc_config_t;
/*section of SOFTWARE INTERFACES DECLARATIONS */

Std_ReturnType ADC_Init(const adc_config_t *_adc);
Std_ReturnType ADC_DeInit(const adc_config_t *_adc);
Std_ReturnType ADC_SelectChannel(const adc_config_t *_adc, adc_channel_select_t channel);
Std_ReturnType ADC_StartConversion(const adc_config_t *_adc);
Std_ReturnType ADC_IsConversionDone(const adc_config_t *_adc, uint8 *conversion_st);
Std_ReturnType ADC_GetConversionResult(const adc_config_t *_adc, adc_result_t *conversion_st);
Std_ReturnType ADC_GetConversion_Blocking(const adc_config_t *_adc, adc_channel_select_t channel ,adc_result_t *conversion_st);
Std_ReturnType ADC_StartConversion_Interrupt(const adc_config_t *_adc, adc_channel_select_t channel);


#endif	/* HAL_ADC_H */

