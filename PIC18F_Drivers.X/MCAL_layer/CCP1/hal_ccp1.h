/* 
 * File:   hal_ccp1.h
 * Author: Naghm Ayman Omar
 *
 * Created on 27 July 2024, 17:03
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H

/*--------------------- section of INCLUDES --------------------- */
#include"pic18f4620.h"
#include"../mcal_std_types.h"
#include"../../MCAL_layer/GPIO/hal_gpio.h"
#include"../../MCAL_layer/Interrupt/mcal_internal_interrupt.h"
#include"ccp1_cfg.h"

/*--------------------- section of MACRO DECLARATIONS --------------------- */
/* Timer2 Input Clock Post-scale Select bits */
#define CCP_TIMER2_POSTSCALER_DIV_BY_1   1
#define CCP_TIMER2_POSTSCALER_DIV_BY_2   2
#define CCP_TIMER2_POSTSCALER_DIV_BY_3   3
#define CCP_TIMER2_POSTSCALER_DIV_BY_4   4
#define CCP_TIMER2_POSTSCALER_DIV_BY_5   5
#define CCP_TIMER2_POSTSCALER_DIV_BY_6   6
#define CCP_TIMER2_POSTSCALER_DIV_BY_7   7
#define CCP_TIMER2_POSTSCALER_DIV_BY_8   8
#define CCP_TIMER2_POSTSCALER_DIV_BY_9   9
#define CCP_TIMER2_POSTSCALER_DIV_BY_10  10
#define CCP_TIMER2_POSTSCALER_DIV_BY_11  11
#define CCP_TIMER2_POSTSCALER_DIV_BY_12  12
#define CCP_TIMER2_POSTSCALER_DIV_BY_13  13
#define CCP_TIMER2_POSTSCALER_DIV_BY_14  14
#define CCP_TIMER2_POSTSCALER_DIV_BY_15  15
#define CCP_TIMER2_POSTSCALER_DIV_BY_16  16
/* CCP_ Input Clock Pre-scale Select bits */
#define CCP_TIMER2_PRESCALER_DIV_BY_1   1
#define CCP_TIMER2_PRESCALER_DIV_BY_4   2
#define CCP_TIMER2_PRESCALER_DIV_BY_16  3


/* CCP1 Module Mode Select */
#define CCP_MODULE_DISABLE                ((uint8)0x00)
#define CCP_CAPTURE_MODE_1_FALLING_EDGE   ((uint8)0x04)
#define CCP_CAPTURE_MODE_1_RISING_EDGE    ((uint8)0x05)
#define CCP_CAPTURE_MODE_4_RISING_EDGE    ((uint8)0x06)
#define CCP_CAPTURE_MODE_16_RISING_EDGE   ((uint8)0x07)
#define CCP_COMPARE_MODE_SET_PIN_LOW      ((uint8)0x08)
#define CCP_COMPARE_MODE_SET_PIN_HIGH     ((uint8)0x09)
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH  ((uint8)0x02)
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT ((uint8)0x0A) 
#define CCP_COMPARE_MODE_GEN_EVENT        ((uint8)0x0B)
#define CCP_PWM_MODE                      ((uint8)0x0C)

/* CCP1 Capture Mode State */
#define CCP1_CAPTURE_NOT_READY  0x00
#define CCP1_CAPTURE_READY      0x01

/* CCP1 Compare Mode State */
#define CCP1_COMPARE_NOT_READY  0x00
#define CCP1_COMPARE_READY      0x01

/*--------------------- section of MACRO FUNCTIONS DECLARATIONS --------------------- */
#define CCP1_SET__MODE(_CONFIG) (CCP1CONbits.CCP1M = _CONFIG)
#define CCP2_SET__MODE(_CONFIG) (CCP2CONbits.CCP2M = _CONFIG)
/*--------------------- section of DATA TYPE DECLARATIONS --------------------- */
typedef union{
    struct {
        uint8 ccp_low;
        uint8 ccp_high;
    };
    struct {
        uint16 ccp_16bit;
    };
}ccp_reg_t;

typedef enum{
    CCP1_INST,
    CCP2_INST,
}ccp_inst_t;

typedef enum{
    CCP1_CCP2_TIMER3 = 0,
    CCP1_TIMER1_CCP2_TIMER3,
    CCP1_CCP2_TIMER1
}ccp_capture_timer_t;
typedef enum{
    CCP1_CAPTURE_MODE_SELECT = 0,
    CCP1_COMPARE_MODE_SELECT,
    CCP1_PWM_MODE_SELECT,
}ccp1_mode_t;

typedef struct {
ccp_inst_t ccp_inst;
ccp1_mode_t ccp_mode;
uint8 ccp_mode_variant;
pin_config_t pin_cfg;
ccp_capture_timer_t ccp_capture_time;

#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(* CCP1_InterruptHandler)(void);
    interrupt_priority_cfg CCP1_priority;
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(* CCP2_InterruptHandler)(void);
    interrupt_priority_cfg CCP2_priority;
#endif
#if (CCP1_CFG__MODE_SELECTED == CCP_CFG_PWM_MODE_SELECT) || (CCP2_CFG__MODE_SELECTED == CCP_CFG_PWM_MODE_SELECT)
    uint32 pmw_frequancy;
    uint8 timer2_postscaler_value : 4;
    uint8 timer2_prescaler_value : 2;
#endif    
}ccp_t;

/*--------------------- section of SOFTWARE INTERFACES DECLARATIONS --------------------- */ 

Std_ReturnType CCP_Init(const ccp_t *_ccp1_obj);
Std_ReturnType CCP_DeInit(const ccp_t *_ccp1_obj);

#if (CCP1_CFG__MODE_SELECTED == CCP_CFG_CAPTURE_MODE_SELECT)
Std_ReturnType CCP1_IsCaptureReady(uint8 *capture_status);
Std_ReturnType CCP1_Capture_Mode_read_Value(uint16 *capture_value);
#endif   

#if (CCP1_CFG__MODE_SELECTED == CCP_CFG_COMPARATOR_MODE_SELECT)
Std_ReturnType CCP_IsCompareCompleted(uint8 *compare_status);
Std_ReturnType CCP_Compare_Mode_Set_Value(const ccp_t *_ccp1_obj,uint16 compare_value);
#endif   

#if (CCP1_CFG__MODE_SELECTED == CCP_CFG_PWM_MODE_SELECT)
Std_ReturnType CCP_PWM_Set_Duty(const ccp_t *_ccp1_obj,const uint8 _duty);
Std_ReturnType CCP_PWM_Start(const ccp_t *_ccp1_obj);
Std_ReturnType CCP_PWM_Stop(const ccp_t *_ccp1_obj);
#endif

#endif	/* HAL_CCP1_H */

