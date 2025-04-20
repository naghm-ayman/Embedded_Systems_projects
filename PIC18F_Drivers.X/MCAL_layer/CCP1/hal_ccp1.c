/* 
 * File:   hal_ccp1.c
 * Author: Naghm Ayman Omar
 *
 * Created on 27 July 2024, 17:03
 */

#include"hal_ccp1.h"

 #if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*CCP1_InterruptHandler)(void) = NULL;
#endif
 #if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*CCP2_InterruptHandler)(void) = NULL;
#endif
static void CCP_interrupt_config(const ccp_t *_ccp_obj);
static void PWM_mode_config(const ccp_t *_ccp_obj);
static void CCP_Mode_Timer_Select(const ccp_t *_ccp_obj);
static Std_ReturnType CCP_Capture_mode_config(const ccp_t *_ccp_obj);
static Std_ReturnType CCP_Compare_mode_config(const ccp_t *_ccp_obj);
Std_ReturnType CCP_Init(const ccp_t *_ccp1_obj){
    Std_ReturnType ret = E_OK;
     
     if(NULL == _ccp1_obj){
         ret= E_NOK;
     }
     else{
         /* Disable the CCP */
         if(CCP1_INST == _ccp1_obj->ccp_inst ){
             CCP1_SET__MODE(CCP_MODULE_DISABLE);
         }
         else if(CCP2_INST == _ccp1_obj->ccp_inst){
             CCP2_SET__MODE(CCP_MODULE_DISABLE); // IF ANY LOGICAL ERROR RETURN TO THE EXPRESSION CCP2CONbits.CCP2M
         }
         else{
             /* Nothing */
         }
         
         /* CCP Module Configure the CAPTURE MODE */
         if(CCP_CFG_CAPTURE_MODE_SELECT == _ccp1_obj->ccp_mode) {
            ret = CCP_Capture_mode_config(_ccp1_obj);
         }
          /* CCP Module Configure the COMPARATOR MODE */
         else if(CCP_CFG_COMPARATOR_MODE_SELECT == _ccp1_obj->ccp_mode){
             ret = CCP_Compare_mode_config(_ccp1_obj);
             
         }
#if (CCP1_CFG__MODE_SELECTED == CCP_CFG_PWM_MODE_SELECT) || (CCP2_CFG__MODE_SELECTED == CCP_CFG_PWM_MODE_SELECT)
         /* CCP1 Module Configure the PWM MODE */
        else if (CCP_CFG_PWM_MODE_SELECT == _ccp1_obj->ccp_mode) 
            /*Configure the PWM mode */
            PWM_mode_config(_ccp1_obj);
#endif   
        else{
             /*Nothing*/
         }
         /*Configure the PIN initialize */
         ret = gpio_pin_intialize(&(_ccp1_obj->pin_cfg));
         /*Configure the Interrupt */
         CCP_interrupt_config(_ccp1_obj);

     }
    
     return(ret);
}
Std_ReturnType CCP_DeInit(const ccp_t *_ccp1_obj){
    Std_ReturnType ret = E_OK;
     
     if(NULL == _ccp1_obj){
         ret= E_NOK;
     }
     else{
         /* Disable the CCP */
         if(CCP1_INST == _ccp1_obj->ccp_inst ){
             CCP1_SET__MODE(CCP_MODULE_DISABLE); // Disable CCP1
         /*Configure the Interrupt */
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            CCP1_InterruptDisable();
#endif
         }
         else if(CCP2_INST == _ccp1_obj->ccp_inst){
             CCP2_SET__MODE(CCP_MODULE_DISABLE); // Disable CCP2
             /*Configure the Interrupt */
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            CCP2_InterruptDisable();
#endif
         }
         else{
             /* Nothing */
         }   

     }
     return(ret);
}

#if (CCP1_CFG__MODE_SELECTED == CCP_CFG_CAPTURE_MODE_SELECT)
Std_ReturnType CCP1_IsCaptureReady(uint8 *capture_status){
    Std_ReturnType ret = E_OK;
     
     if(NULL == capture_status){
         ret= E_NOK;
     }
     else{
         if(CCP1_CAPTURE_READY == PIR1bits.CCP1IF){
             *capture_status = CCP1_CAPTURE_READY;
             CCP1_InterruptFlagClear();
         }
         else{
             *capture_status = CCP1_CAPTURE_NOT_READY;
         }
    
     }
     return(ret);
}
Std_ReturnType CCP1_Capture_Mode_read_Value(uint16 *capture_value){
    Std_ReturnType ret = E_OK;
     ccp_reg_t capture_temp_val = {.ccp_low = 0, .ccp_high = 0};
     if(NULL == capture_value){
         ret= E_NOK;
     }
     else{
         capture_temp_val.ccp_low = CCPR1L;
         capture_temp_val.ccp_high = CCPR1H;
         *capture_value = capture_temp_val.ccp_16bit;
     }
     return(ret);
}
#endif   

#if (CCP1_CFG__MODE_SELECTED == CCP_CFG_COMPARATOR_MODE_SELECT)
Std_ReturnType CCP_IsCompareCompleted(uint8 *compare_status){
     Std_ReturnType ret = E_OK;
     
     if(NULL == compare_status){
         ret= E_NOK;
     }
     else{
          if(CCP1_COMPARE_READY == PIR1bits.CCP1IF){
             *compare_status = CCP1_COMPARE_READY;
             CCP1_InterruptFlagClear();
         }
         else{
             *compare_status = CCP1_COMPARE_NOT_READY;
         }
     }
     return(ret);
}
Std_ReturnType CCP_Compare_Mode_Set_Value(const ccp_t *_ccp1_obj,uint16 compare_value){
     Std_ReturnType ret = E_OK;
     ccp_reg_t capture_temp_val = {.ccp_low = 0, .ccp_high = 0};
     if(NULL == _ccp1_obj){
         ret= E_NOK;
     }
     else{
         capture_temp_val.ccp_16bit = compare_value;
          if(CCP1_INST == _ccp1_obj->ccp_inst ){     
             CCPR1L = capture_temp_val.ccp_low;
             CCPR1H = capture_temp_val.ccp_high;
         }
         else if(CCP2_INST == _ccp1_obj->ccp_inst){
            CCPR2L = capture_temp_val.ccp_low;
            CCPR2H = capture_temp_val.ccp_high;
         }
         else{
             /* Nothing */
         }
     }
     return(ret);
}
#endif   

#if (CCP1_CFG__MODE_SELECTED == CCP_CFG_PWM_MODE_SELECT)
Std_ReturnType CCP_PWM_Set_Duty(const ccp_t *_ccp1_obj,const uint8 _duty){
    Std_ReturnType ret = E_OK;
    uint16 l_duty_temp = 0;
    if(NULL == _ccp1_obj){
         ret= E_NOK;
     }
     else{
        l_duty_temp = (uint16)(4 * (PR2 + 1) * (_duty / 100.0));
         if(CCP1_INST == _ccp1_obj->ccp_inst ){     
             CCP1CONbits.DC1B = (uint8)(l_duty_temp & 0x0003);
             CCPR1L = (uint8)(l_duty_temp >> 2);
         }
         else if(CCP2_INST == _ccp1_obj->ccp_inst){
             CCP2CONbits.DC2B = (uint8)(l_duty_temp & 0x0003);
             CCPR2L = (uint8)(l_duty_temp >> 2);
         }
         else{
             /* Nothing */
         }
      
    
     }
     return(ret);
}
Std_ReturnType CCP_PWM_Start(const ccp_t *_ccp1_obj){
    Std_ReturnType ret = E_OK;
     if(NULL == _ccp1_obj){
         ret= E_NOK;
     }
     else{
         if(CCP1_INST == _ccp1_obj->ccp_inst ){
             CCP1_SET__MODE(CCP_PWM_MODE);
         }
         else if(CCP2_INST == _ccp1_obj->ccp_inst){
             CCP2_SET__MODE(CCP_PWM_MODE); // IF ANY LOGICAL ERROR RETURN TO THE EXPRESSION CCP2CONbits.CCP2M
         }
         else{
             /* Nothing */
         }
      
     }
   
     return(ret);
}
Std_ReturnType CCP_PWM_Stop(const ccp_t *_ccp1_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == _ccp1_obj){
         ret= E_NOK;
     }
     else{
         if(CCP1_INST == _ccp1_obj->ccp_inst ){
             CCP1_SET__MODE(CCP_MODULE_DISABLE);// IF ANY LOGICAL ERROR RETURN TO THE EXPRESSION CCP1CONbits.CCP1M
         }
         else if(CCP2_INST == _ccp1_obj->ccp_inst){
             CCP2_SET__MODE(CCP_MODULE_DISABLE); // IF ANY LOGICAL ERROR RETURN TO THE EXPRESSION CCP2CONbits.CCP2M
         }
         else{
             /* Nothing */
         }
      
     }
     return(ret);
}
#endif

void CCP1_ISR(void){
    CCP1_InterruptFlagClear();
    if(CCP1_InterruptHandler){
       CCP1_InterruptHandler();
    }
    else{
        /* Nothing*/
    }
}
void CCP2_ISR(void){
    CCP2_InterruptFlagClear();
    if(CCP2_InterruptHandler){
       CCP2_InterruptHandler();
    }
    else{
        /* Nothing*/
    }
}
#if (CCP1_CFG__MODE_SELECTED == CCP_CFG_PWM_MODE_SELECT) || (CCP2_CFG__MODE_SELECTED == CCP_CFG_PWM_MODE_SELECT)
static void PWM_mode_config(const ccp_t *_ccp_obj){
    if (CCP1_INST == _ccp_obj->ccp_inst) {
            if (CCP_PWM_MODE == _ccp_obj->ccp_mode_variant) {
                CCP1_SET__MODE(CCP_PWM_MODE);
            } else {
                /*Nothing*/
            }
        } else if (CCP2_INST == _ccp_obj->ccp_inst) {
            if (CCP_PWM_MODE == _ccp_obj->ccp_mode_variant) {
                CCP2_SET__MODE(CCP_PWM_MODE);
            } else {
                /*Nothing*/
            }
        } else {
            /* Nothing */
        }

        /* PWM Frequency Initialization */
        PR2 = (uint8) ((_XTAL_FREQ / (_ccp_obj->pmw_frequancy * 4.0 * _ccp_obj->timer2_postscaler_value
                * _ccp_obj->timer2_postscaler_value) - 1));

    }

#endif
static void CCP_interrupt_config(const ccp_t *_ccp_obj){
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    CCP1_InterruptEnable();
    CCP1_InterruptFlagClear();
    CCP1_InterruptHandler = _ccp_obj->CCP1_InterruptHandler;
    /*Configure the Interrupt Priority Levels */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PriortyLevelEnable();
    if (Interrupt_High_Priority == _ccp_obj->CCP1_priority) {
        INTERRUPT_GlobalInterruptHighEnable();
        CCP1_HighPrioritySet();
    } else if (Interrupt_Low_Priority == _ccp_obj->CCP1_priority) {
        INTERRUPT_GlobalInterruptLowEnable();
        CCP1_LowPrioritySet();
    } else {

    }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    CCP2_InterruptEnable();
    CCP2_InterruptFlagClear();
    CCP2_InterruptHandler = _ccp_obj->CCP2_InterruptHandler;
    /*Configure the Interrupt Priority Levels */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PriortyLevelEnable();
    if (Interrupt_High_Priority == _ccp_obj->CCP2_priority) {
        INTERRUPT_GlobalInterruptHighEnable();
        CCP2_HighPrioritySet();
    } else if (Interrupt_Low_Priority == _ccp_obj->CCP2_priority) {
        INTERRUPT_GlobalInterruptLowEnable();
        CCP2_LowPrioritySet();
    } else {

    }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
}
static void CCP_Mode_Timer_Select(const ccp_t *_ccp_obj){
    if(CCP1_CCP2_TIMER3 == _ccp_obj->ccp_capture_time){
        /* TIMER3 is the Capture/Compare timer for the CCP module */
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 1;
    }
    else if(CCP1_TIMER1_CCP2_TIMER3 == _ccp_obj->ccp_capture_time){
        /* TIMER3 is the Capture/Compare timer for the CCP2 module */
        /* TIMER1 is the Capture/Compare timer for the CCP1 module */
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 0;
    }
    else if(CCP1_CCP2_TIMER1 == _ccp_obj->ccp_capture_time){
        /* TIMER1 is the Capture/Compare timer for the CCP module */
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 0;
    }
    else{
        /* Nothing */
    }
}
static Std_ReturnType CCP_Capture_mode_config(const ccp_t *_ccp_obj) {
    Std_ReturnType ret = E_OK;
    if (CCP1_INST == _ccp_obj->ccp_inst) {
        switch (_ccp_obj->ccp_mode_variant) {
            case CCP_CAPTURE_MODE_1_FALLING_EDGE:
                CCP1_SET__MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);
                break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE:
                CCP1_SET__MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE:
                CCP1_SET__MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE:
                CCP1_SET__MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);
                break;
            default: ret = E_NOK;
        }
    } else if (CCP2_INST == _ccp_obj->ccp_inst) {
        switch (_ccp_obj->ccp_mode_variant) {
            case CCP_CAPTURE_MODE_1_FALLING_EDGE:
                CCP2_SET__MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);
                break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE:
                CCP2_SET__MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE:
                CCP2_SET__MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE:
                CCP2_SET__MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);
                break;
            default: ret = E_NOK;
        }
    } else {
        /* Nothing */
    }
    CCP_Mode_Timer_Select(_ccp_obj);
    return (ret);
}

static Std_ReturnType CCP_Compare_mode_config(const ccp_t *_ccp_obj) {
    Std_ReturnType ret = E_OK;
    if (CCP1_INST == _ccp_obj->ccp_inst) {
         switch (_ccp_obj->ccp_mode_variant) {
                case CCP_COMPARE_MODE_SET_PIN_LOW:
                    CCP1_SET__MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
                    break;
                case CCP_COMPARE_MODE_SET_PIN_HIGH:
                    CCP1_SET__MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
                    break;
                case CCP_COMPARE_MODE_TOGGLE_ON_MATCH:
                    CCP1_SET__MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);
                    break;
                case CCP_COMPARE_MODE_GEN_SW_INTERRUPT:
                    CCP1_SET__MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);
                    break;
                case CCP_COMPARE_MODE_GEN_EVENT:
                    CCP1_SET__MODE(CCP_COMPARE_MODE_GEN_EVENT);
                    break;
                default: ret = E_NOK;
             }
    } else if (CCP2_INST == _ccp_obj->ccp_inst) {
         switch (_ccp_obj->ccp_mode_variant) {
                case CCP_COMPARE_MODE_SET_PIN_LOW:
                    CCP2_SET__MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
                    break;
                case CCP_COMPARE_MODE_SET_PIN_HIGH:
                    CCP2_SET__MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
                    break;
                case CCP_COMPARE_MODE_TOGGLE_ON_MATCH:
                    CCP2_SET__MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);
                    break;
                case CCP_COMPARE_MODE_GEN_SW_INTERRUPT:
                    CCP2_SET__MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);
                    break;
                case CCP_COMPARE_MODE_GEN_EVENT:
                    CCP2_SET__MODE(CCP_COMPARE_MODE_GEN_EVENT);
                    break;
                default: ret = E_NOK;
             }
    } else {
        /* Nothing */
    }
    CCP_Mode_Timer_Select(_ccp_obj);
    return (ret);
}