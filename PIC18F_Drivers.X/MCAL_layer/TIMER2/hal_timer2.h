/* 
 * File:   hal_timer2.h
 * Author: Naghm Ayman Omar
 *
 * Created on 26 July 2024, 14:32
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/*section of INCLUDES */
#include"pic18f4620.h"
#include"../mcal_std_types.h"
#include"../../MCAL_layer/GPIO/hal_gpio.h"
#include"../../MCAL_layer/Interrupt/mcal_internal_interrupt.h"

/*section of DATA TYPE DECLARATIONS*/
/* Timer2 Input Clock Post-scale Select bits */
#define TIMER2_POSTSCALER_DIV_BY_1   0
#define TIMER2_POSTSCALER_DIV_BY_2   1
#define TIMER2_POSTSCALER_DIV_BY_3   2
#define TIMER2_POSTSCALER_DIV_BY_4   3
#define TIMER2_POSTSCALER_DIV_BY_5   4
#define TIMER2_POSTSCALER_DIV_BY_6   5
#define TIMER2_POSTSCALER_DIV_BY_7   6
#define TIMER2_POSTSCALER_DIV_BY_8   7
#define TIMER2_POSTSCALER_DIV_BY_9   8
#define TIMER2_POSTSCALER_DIV_BY_10  9
#define TIMER2_POSTSCALER_DIV_BY_11  10
#define TIMER2_POSTSCALER_DIV_BY_12  11
#define TIMER2_POSTSCALER_DIV_BY_13  12
#define TIMER2_POSTSCALER_DIV_BY_14  13
#define TIMER2_POSTSCALER_DIV_BY_15  14
#define TIMER2_POSTSCALER_DIV_BY_16  15
/* Timer2 Input Clock Pre-scale Select bits */
#define TIMER2_PRESCALER_DIV_BY_1   0
#define TIMER2_PRESCALER_DIV_BY_4   1
#define TIMER2_PRESCALER_DIV_BY_16  2

/*section of MACRO FUNCTIONS DECLARATIONS */
/* Enable / Disable Timer1 Module */
#define TIMER2_MODULE_ENABLE()             (T2CONbits.TMR2ON = 1)
#define TIMER2_MODULE_DISABLE()            (T2CONbits.TMR2ON = 0)

/* Timer2 Input Clock Pre-scale Select bits */
#define TIMER2_PRESCALER_SELSCT(_PRESCALER_) (T2CONbits.T2CKPS = _PRESCALER_)
/* Timer2 Input Clock Post-scale Select bits */
#define TIMER2_POSTSCALER_SELSCT(_POSTSCALER_) (T2CONbits.TOUTPS = _POSTSCALER_)

/*section of DATA TYPES DECLARATIONS */
typedef struct{
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(* TIMER2_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint8 timer2_preload_value;
    uint8 timer2_postscaler_value : 4;
    uint8 timer2_prescaler_value : 2;
    uint8 timer2_reserved : 2;
}timer2_t;

/*section of SOFTWARE INTERFACES DECLARATIONS */
Std_ReturnType TIMER2_Init(const timer2_t *_timer);
Std_ReturnType TIMER2_DeInit(const timer2_t *_timer);
Std_ReturnType TIMER2_Write_value(const timer2_t *_timer, uint8 _value);
Std_ReturnType TIMER2_Read_value(const timer2_t *_timer, uint8 *_value);

#endif	/* HAL_TIMER2_H */

