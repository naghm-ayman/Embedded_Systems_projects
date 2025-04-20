/* 
 * File:   mcal_interrupt_config.h
 * Author: Naghm Ayman Omar
 *
 * Created on 08 July 2024, 14:28
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/*section of INCLUDES */
#include "pic18f4620.h"
#include"../../MCAL_layer/GPIO/hal_gpio.h"
#include"../mcal_std_types.h"
#include"mcal_interrupt_gen_cfg.h"

/*section of MACRO FUNCTIONS DECLARATIONS */
#define INTERRUPT_ENABLE               1
#define INTERRUPT_DISABLE              0
#define INTERRUPT_OCCUR                1
#define INTERRUPT_NOT_OCCUR            0 
#define INTERRUPT_PRIORITY_ENABLE      1
#define INTERRUPT_PRIORITY_DISABLE     0

/*section of MACRO DECLARATIONS */

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

/* this macro will enable priority level on interrupts */
#define INTERRUPT_PriortyLevelEnable()  (RCONbits.IPEN = 1)
/* this macro will enable priority level on interrupts */
#define INTERRUPT_PriortyLevelDisable() (RCONbits.IPEN = 0)

/* this macro will enable high priority global interrupts */
#define INTERRUPT_GlobalInterruptHighEnable()  (INTCONbits.GIEH = 1)
/* this macro will disable high priority global interrupts */
#define INTERRUPT_GlobalInterruptHighDisable() (INTCONbits.GIEH = 0)

/* this macro will enable low priority global interrupts */
#define INTERRUPT_GlobalInterruptLowEnable()  (INTCONbits.GIEL = 1)
/* this macro will disable low priority global interrupts */
#define INTERRUPT_GlobalInterruptLowDisable() (INTCONbits.GIEL = 0)

#else

/* this macro will enable global interrupts */
#define INTERRUPT_GlobalInterruptEnable()  (INTCONbits.GIE = 1)
/* this macro will disable global interrupts */
#define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0)

/* this macro will enable peripheral interrupts */
#define INTERRUPT_PeripheralInterruptEnable()  (INTCONbits.PEIE = 1)
/* this macro will disable peripheral interrupts */
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)

#endif

typedef enum {
    Interrupt_Low_Priority = 0,
    Interrupt_High_Priority     
}interrupt_priority_cfg; 

/*section of FUNCTIONS DECLARATIONS*/


#endif	/* MCAL_INTERRUPT_CONFIG_H */

