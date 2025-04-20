/* 
 * File:   hal_timer3.c
 * Author: Naghm Ayman Omar
 *
 * Created on 26 July 2024, 14:32
 */

#include"hal_timer3.h"

#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TIMER3_InterruptHandler)(void) = NULL;
#endif

static uint16 timer3_preload = ZERO_INIT;

static inline void TIMER3_MODE_Select(const timer3_t *_timer);

Std_ReturnType TIMER3_Init(const timer3_t *_timer){
    Std_ReturnType ret = E_OK;
     
     if(NULL == _timer){
         ret= E_NOK;
     }
     else{
         /* Disable the timer */
        TIMER3_MODULE_DISABLE();
        TIMER3_PRESCALER_SELSCT(_timer->timer3_prescaler_value);
        TIMER3_MODE_Select(_timer);
        TMR1H = (_timer->timer3_preload_value) >> 8;
        TMR1L = (uint8)(_timer->timer3_preload_value);
        timer3_preload = _timer->timer3_preload_value;
        
         /*Configure the Interrupt */
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
         TIMER3_InterruptEnable();
            TIMER3_InterruptFlagClear();
            TIMER3_InterruptHandler = _timer->TIMER3_InterruptHandler;
  /*Configure the Interrupt Priority Levels */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
           INTERRUPT_PriortyLevelEnable();
          if(Interrupt_High_Priority == _timer->priority){
              INTERRUPT_GlobalInterruptHighEnable();
              TIMER3_HighPrioritySet();
          }
          else if(Interrupt_Low_Priority == _timer->priority){
              INTERRUPT_GlobalInterruptLowEnable();
              TIMER3_LowPrioritySet();
          }
          else{
              
          }
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
         
         /* Enable the timer*/
         TIMER3_MODULE_ENABLE();
     }
     return(ret);
}
Std_ReturnType TIMER3_DeInit(const timer3_t *_timer){
     Std_ReturnType ret = E_OK;
     
     if(NULL == _timer){
         ret= E_NOK;
     }
     else{
          TIMER3_MODULE_DISABLE();

#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            TIMER3_InterruptDisable();
#endif
     }
     return(ret);
}
Std_ReturnType TIMER3_Write_value(const timer3_t *_timer, uint16  _value){
     Std_ReturnType ret = E_OK;
     
     if(NULL == _timer){
         ret= E_NOK;
     }
     else{
          TMR3H = (_value) >> 8;
          TMR3L = (uint8)(_value);
     }
     return(ret);
}
Std_ReturnType TIMER3_Read_value(const timer3_t *_timer, uint16 *_value){
    Std_ReturnType ret = E_OK;
     uint8 l_tmr3h = ZERO_INIT, l_tmr3l = ZERO_INIT;
     if((NULL == _timer) || (NULL == _value)){
         ret= E_NOK;
     }
     else{
         l_tmr3l = TMR1L;
         l_tmr3h = TMR1H;
         *_value = (uint16)((l_tmr3h << 8) + l_tmr3l);
     }
     return(ret);
}

void TIMER3_ISR(void){
    TIMER3_InterruptFlagClear();
    TMR3H = (timer3_preload) >> 8;
    TMR3L = (uint8)(timer3_preload);
    if(TIMER3_InterruptHandler){
       TIMER3_InterruptHandler();
        
    }
}
static inline void TIMER3_MODE_Select(const timer3_t *_timer){
    if(TIMER3_TIMER_MODE == _timer->timer3_mode){
        TIMER3_TIMER_MODE_ENABLE();
    }
    else if(TIMER3_COUNTER_MODE == _timer->timer3_mode){
        TIMER3_CONTROL_MODE_ENABLE();
        if(TIMER3_ASYNC_COUNTER_MODE == _timer->timer3_counter_mode){
            TIMER3_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if(TIMER3_SYNC_COUNTER_MODE == _timer->timer3_counter_mode){
            TIMER3_SYNC_COUNTER_MODE_ENABLE();
        }
        else{
        /* Nothing */
        }  
    }
    else{
        /* Nothing */
    }
}