/* 
 * File:   hal_timer3.h
 * Author: Naghm Ayman Omar
 *
 * Created on 26 July 2024, 14:32
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/*section of INCLUDES */
#include"pic18f4620.h"
#include"../mcal_std_types.h"
#include"../../MCAL_layer/GPIO/hal_gpio.h"
#include"../../MCAL_layer/Interrupt/mcal_internal_interrupt.h"

/*section of DATA TYPE DECLARATIONS*/
#define TIMER3_COUNTER_MODE 1
#define TIMER3_TIMER_MODE   0

#define TIMER3_ASYNC_COUNTER_MODE  1
#define TIMER3_SYNC_COUNTER_MODE   0

/* Timer3 Input Clock Pre-scale Select bits */
#define TIMER3_PRESCALER_DIV_BY_1  0
#define TIMER3_PRESCALER_DIV_BY_2  1
#define TIMER3_PRESCALER_DIV_BY_4  2
#define TIMER3_PRESCALER_DIV_BY_8  3
/*  16-Bit Read/Write Mode Bits */
#define TIMER3_RW_REG_8BITS_MODE  0
#define TIMER3_RW_REG_16BITS_MODE 1

/*section of MACRO DECLARATIONS */
/* Enable / Disable Timer3 Module */
#define TIMER3_MODULE_ENABLE()             (T3CONbits.TMR3ON = 1)
#define TIMER3_MODULE_DISABLE()            (T3CONbits.TMR3ON = 0)
/* Timer3 Module Clock Source */
#define TIMER3_TIMER_MODE_ENABLE()         (T3CONbits.TMR3CS = 0)
#define TIMER3_CONTROL_MODE_ENABLE()       (T3CONbits.TMR3CS = 1)
/* Timer3 External Clock Input Sync */
#define TIMER3_ASYNC_COUNTER_MODE_ENABLE() (T3CONbits.T3SYNC = 1)
#define TIMER3_SYNC_COUNTER_MODE_ENABLE()  (T3CONbits.T3SYNC = 0)
/* Timer3 Input Clock Pre-scale Select bits */
#define TIMER3_PRESCALER_SELSCT(_PRESCALER_) (T3CONbits.T3CKPS = _PRESCALER_)
/*  16-Bit Read/Write Mode Bits */
#define TIMER3_RW_REG_8BITS_MODE_ENABLE()   (T3CONbits.RD16 = 0)
#define TIMER3_RW_REG_16BITS_MODE_ENABLE()  (T3CONbits.RD16 = 1)
/*section of MACRO FUNCTIONS DECLARATIONS */

typedef struct{
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(* TIMER3_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint16 timer3_preload_value;
    uint8 timer3_prescaler_value : 2;
    uint8 timer3_mode : 1;
    uint8 timer3_counter_mode : 1;
    uint8 timer3_osc_cgf : 1;
    uint8 timer3_reg_rw_mode : 1;
    uint8 timer3_reserved : 3;
}timer3_t;

/*section of SOFTWARE INTERFACES DECLARATIONS */

Std_ReturnType TIMER3_Init(const timer3_t *_timer);
Std_ReturnType TIMER3_DeInit(const timer3_t *_timer);
Std_ReturnType TIMER3_Write_value(const timer3_t *_timer, uint16  _value);
Std_ReturnType TIMER3_Read_value(const timer3_t *_timer, uint16 *_value);

#endif	/* HAL_TIMER3_H */

