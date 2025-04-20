/* 
 * File:   hal_timer0.h
 * Author: Naghm Ayman Omar
 *
 * Created on 23 July 2024, 14:10
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/*section of INCLUDES */
#include"pic18f4620.h"
#include"../mcal_std_types.h"
#include"../../MCAL_layer/GPIO/hal_gpio.h"
#include"../../MCAL_layer/Interrupt/mcal_internal_interrupt.h"

/*section of DATA TYPE DECLARATIONS*/
#define TIMER0_TIMER_MODE_ENABLE_CFG   1
#define TIMER0_COUNTER_MODE_ENABLE_CFG 0

#define TIMER0_PRESCALER_ENABLE_CFG  1
#define TIMER0_PRESCALER_DISABLE_CFG 0

#define TIMER0_RISING_EDGE_ENABLE_CFG  1
#define TIMER0_FALLING_EDGE_ENABLE_CFG 0

#define TIMER0_8_BITS_REGISTER_MODE  1
#define TIMER0_16_BITS_REGISTER_MODE 0


/*section of MACRO DECLARATIONS */
#define TIMER0_PRESCALER_ENABLE()   (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE()  (T0CONbits.PSA = 1)

#define TIMER0_RISING_EDGE_ENABLE()   (T0CONbits.T0SE = 0)
#define TIMER0_FALLING_EDGE_ENABLE()  (T0CONbits.T0SE = 1)

#define TIMER0_TIMER_MODE_ENABLE()   (T0CONbits.T0CS = 0)
#define TIMER0_CONTROL_MODE_ENABLE() (T0CONbits.T0CS = 1)

#define TIMER0_16_BITS_REGISTER_ENABLE() (T0CONbits.T08BIT = 0)
#define TIMER0_8_BITS_REGISTER_ENABLE()  (T0CONbits.T08BIT = 1)

#define TIMER0_MODULE_ENABLE()  (T0CONbits.TMR0ON = 1)
#define TIMER0_MODULE_DISABLE() (T0CONbits.TMR0ON = 0)
/*section of MACRO FUNCTIONS DECLARATIONS */

typedef enum{
    TIMER0_PRESCALER_DIV_BY_2 = 0,
    TIMER0_PRESCALER_DIV_BY_4,         
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,         
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256 
}timer0_prescaler_select_t;

typedef struct{
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(* TIMER0_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    timer0_prescaler_select_t  prescaler_value;
    uint16 timer0_preload_value;
    uint8 prescaler_enable : 1;
    uint8 timer0_counter_edge : 1;
    uint8 timer0_mode : 1;
    uint8 timer0_register_size: 1;
    uint8 timer0_preserved : 4;

}timer0_t;
/*section of SOFTWARE INTERFACES DECLARATIONS */

Std_ReturnType TIMER0_Init(const timer0_t *_timer);
Std_ReturnType TIMER0_DeInit(const timer0_t *_timer);
Std_ReturnType TIMER0_Write_value(const timer0_t *_timer, uint16 _value);
Std_ReturnType TIMER0_Read_value(const timer0_t *_timer, uint16 *_value);

#endif	/* HAL_TIMER0_H */

