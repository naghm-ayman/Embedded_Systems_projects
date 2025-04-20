/* 
 * File:   hal_timer1.h
 * Author: Naghm Ayman Omar
 *
 * Created on 25 July 2024, 17:02
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/*---------------------- section of INCLUDES ----------------------*/
#include"pic18f4620.h"
#include"../mcal_std_types.h"
#include"../../MCAL_layer/GPIO/hal_gpio.h"
#include"../../MCAL_layer/Interrupt/mcal_internal_interrupt.h"

/*---------------------- section of MACRO DECLARATIONS ----------------------*/
#define TIMER1_COUNTER_MODE 1
#define TIMER1_TIMER_MODE   0

#define TIMER1_ASYNC_COUNTER_MODE  1
#define TIMER1_SYNC_COUNTER_MODE   0
/* Timer1 Oscillator Bit */
#define TIMER1_OSCILLATOR_ENABLE   1
#define TIMER1_OSCILLATOR_DISABLE  0
/* Timer1 Input Clock Pre-scale Select bits */
#define TIMER1_PRESCALER_DIV_BY_1  0
#define TIMER1_PRESCALER_DIV_BY_2  1
#define TIMER1_PRESCALER_DIV_BY_4  2
#define TIMER1_PRESCALER_DIV_BY_8  3
/*  16-Bit Read/Write Mode Bits */
#define TIMER1_RW_REG_8BITS_MODE  0
#define TIMER1_RW_REG_16BITS_MODE 1

/*---------------------- section of MACRO FUNCTIONS DECLARATIONS ---------------------- */

/* Enable / Disable Timer1 Module */
#define TIMER1_MODULE_ENABLE()             (T1CONbits.TMR1ON = 1)
#define TIMER1_MODULE_DISABLE()            (T1CONbits.TMR1ON = 0)
/* Timer1 Module Clock Source */
#define TIMER1_TIMER_MODE_ENABLE()         (T1CONbits.TMR1CS = 0)
#define TIMER1_CONTROL_MODE_ENABLE()       (T1CONbits.TMR1CS = 1)
/* Timer1 External Clock Input Sync */
#define TIMER1_ASYNC_COUNTER_MODE_ENABLE() (T1CONbits.T1SYNC = 1)
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()  (T1CONbits.T1SYNC = 0)
/* Timer1 Oscillator Bit */
#define TIMER1_OSC_HW_ENABLE()             (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSC_HW_DISABLE()            (T1CONbits.T1OSCEN = 0)
/* Timer1 Input Clock Pre-scale Select bits */
#define TIMER1_PRESCALER_SELSCT(_PRESCALER_) (T1CONbits.T1CKPS = _PRESCALER_)
/* Timer1 System Clock Status */
#define TIMER1_SYSTEM_CLK_STATUS()         (T1CONbits.T1RUN)
/*  16-Bit Read/Write Mode Bits */
#define TIMER1_RW_REG_8BITS_MODE_ENABLE()   (T1CONbits.RD16 = 0)
#define TIMER1_RW_REG_16BITS_MODE_ENABLE()  (T1CONbits.RD16 = 1)



/*---------------------- section of DATA TYPE DECLARATIONS---------------------- */

typedef struct{
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(* TIMER1_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint16 timer1_preload_value;
    uint8 timer1_prescaler_value : 2;
    uint8 timer1_mode : 1;
    uint8 timer1_counter_mode : 1;
    uint8 timer1_osc_cgf : 1;
    uint8 timer1_reg_rw_mode : 1;
    uint8 timer1_reserved : 2;
}timer1_t;

/*---------------------- section of SOFTWARE INTERFACES DECLARATIONS ---------------------- */

Std_ReturnType TIMER1_Init(const timer1_t *_timer);
Std_ReturnType TIMER1_DeInit(const timer1_t *_timer);
Std_ReturnType TIMER1_Write_value(const timer1_t *_timer, uint16  _value);
Std_ReturnType TIMER1_Read_value(const timer1_t *_timer, uint16 *_value);



#endif	/* HAL_TIMER1_H */

