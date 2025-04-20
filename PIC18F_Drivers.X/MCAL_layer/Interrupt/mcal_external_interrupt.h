/* 
 * File:   mcal_external_interrupt.h
 * Author: Naghm Ayman Omar
 *
 * Created on 08 July 2024, 14:29
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/*section of INCLUDES */
#include"mcal_interrupt_config.h"

/*section of MACRO DECLARATIONS */

#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* this routine clears the interrupt enable of the external interrupt , INT0 */
#define EXT_INT0_InterruptDisable()  (INTCONbits.INT0IE = 0)
/* this routine sets the interrupt enable of the external interrupt , INT0 */
#define EXT_INT0_InterruptEnable()   (INTCONbits.INT0IE = 1)
/* this routine clears the interrupt flag of the external interrupt , INT0 */
#define EXT_INT0_InterruptFlagClear()  (INTCONbits.INT0IF = 0)
/* this routine sets the edge of the external interrupt to negative edge , INT0 */
#define EXT_INT0_RisingEdge()   (INTCON2bits.INTEDG0 = 1)
/* this routine sets the edge of the external interrupt to positive edge , INT0 */
#define EXT_INT0_FallingEdge()   (INTCON2bits.INTEDG0 = 0)


/* this routine clears the interrupt enable of the external interrupt , INT1 */
#define EXT_INT1_InterruptDisable()  (INTCON3bits.INT1IE = 0)
/* this routine sets the interrupt enable of the external interrupt , INT1 */
#define EXT_INT1_InterruptEnable()   (INTCON3bits.INT1IE = 1)
/* this routine clears the interrupt flag of the external interrupt , INT1 */
#define EXT_INT1_InterruptFlagClear()  (INTCON3bits.INT1IF = 0)
/* this routine sets the edge of the external interrupt to negative edge , INT1 */
#define EXT_INT1_RisingEdge()   (INTCON2bits.INTEDG1 = 1)
/* this routine sets the edge of the external interrupt to positive edge , INT1 */
#define EXT_INT1_FallingEdge()   (INTCON2bits.INTEDG1 = 0)


/* this routine clears the interrupt enable of the external interrupt , INT2 */
#define EXT_INT2_InterruptDisable()  (INTCON3bits.INT2IE = 0)
/* this routine sets the interrupt enable of the external interrupt , INT2 */
#define EXT_INT2_InterruptEnable()   (INTCON3bits.INT2IE = 1)
/* this routine clears the interrupt flag of the external interrupt , INT2 */
#define EXT_INT2_InterruptFlagClear()  (INTCON3bits.INT2IF = 0)
/* this routine sets the edge of the external interrupt to negative edge , INT2 */
#define EXT_INT2_RisingEdge()   (INTCON2bits.INTEDG2 = 1)
/* this routine sets the edge of the external interrupt to positive edge , INT2 */
#define EXT_INT2_FallingEdge()   (INTCON2bits.INTEDG2 = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* this routine sets the INT1 External interrupt to be high priority */
#define EXT_INT1_HighPrioritySet()  (INTCON3bits.INT1IP = 1)
/* this routine sets the INT1 External interrupt to be low priority */
#define EXT_INT1_LowPrioritySet()   (INTCON3bits.INT1IP = 0)
/* this routine sets the INT2 External interrupt to be high priority */
#define EXT_INT2_HighPrioritySet()  (INTCON3bits.INT2IP = 1)
/* this routine sets the INT2 External interrupt to be low priority */
#define EXT_INT2_LowPrioritySet()   (INTCON3bits.INT2IP = 0)
#endif

#endif

#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this routine clears the interrupt enable of the external interrupt , RBx */
#define EXT_RBx_InterruptDisable()  (INTCONbits.RBIE = 0)
/* this routine sets the interrupt enable of the external interrupt , RBx */
#define EXT_RBx_InterruptEnable()   (INTCONbits.RBIE = 1)
/* this routine clears the interrupt flag of the external interrupt , RBx */
#define EXT_RBx_InterruptFlagClear()  (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* this routine sets the RBx External interrupt to be high priority */
#define EXT_RBx_HighPrioritySet()  (INTCON2bits.RBIP = 1)
/* this routine sets the RBx External interrupt to be low priority */
#define EXT_RBx_LowPrioritySet()   (INTCON2bits.RBIP = 0)

#endif

#endif

/*section of DATA TYPE DECLARATIONS */
typedef void(*InterruptHandler)(void);

typedef enum {
    Interrupt_Falling_Edge = 0,
    Interrupt_Rising_Edge     
}interrupt_INTx_edge;

typedef enum {
    Interrupt_External_INT0 = 0,
    Interrupt_External_INT1,
    Interrupt_External_INT2
}interrupt_INTx_scr;

typedef struct {
    void (*EXT_InterruptHandler) (void);
    pin_config_t mcu_pin;
    interrupt_INTx_edge edge;
    interrupt_INTx_scr source;
    interrupt_priority_cfg priority;
}interrupt_INTx_t;

typedef struct {
    void (*EXT_InterruptHandler_HIGH) (void);
    void (*EXT_InterruptHandler_LOW) (void);
    pin_config_t mcu_pin;
    interrupt_priority_cfg priority;
}interrupt_RBx_t;

/*section of FUNCTIONS DECLARATIONS*/
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *inturrpt_obj);
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *inturrpt_obj);
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *inturrpt_obj);
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *inturrpt_obj);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

