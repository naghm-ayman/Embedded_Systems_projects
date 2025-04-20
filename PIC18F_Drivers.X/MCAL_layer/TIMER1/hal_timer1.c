/* 
 * File:   hal_timer1.c
 * Author: Naghm Ayman Omar
 *
 * Created on 25 July 2024, 17:02
 */

#include"hal_timer1.h"

#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TIMER1_InterruptHandler)(void) = NULL;
#endif

static uint16 timer1_preload = ZERO_INIT;

static inline void TIMER1_MODE_Select(const timer1_t *_timer);
Std_ReturnType TIMER1_Init(const timer1_t *_timer){
      Std_ReturnType ret = E_OK;
     
     if(NULL == _timer){
         ret= E_NOK;
     }
     else{
         /* Disable the timer */
        TIMER1_MODULE_DISABLE();
        TIMER1_PRESCALER_SELSCT(_timer->timer1_prescaler_value);
        TIMER1_MODE_Select(_timer);
        TMR1H = (_timer->timer1_preload_value) >> 8;
        TMR1L = (uint8)(_timer->timer1_preload_value);
        timer1_preload = _timer->timer1_preload_value;
        
         /*Configure the Interrupt */
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
         TIMER1_InterruptEnable();
            TIMER1_InterruptFlagClear();
            TIMER1_InterruptHandler = _timer->TIMER1_InterruptHandler;
  /*Configure the Interrupt Priority Levels */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
           INTERRUPT_PriortyLevelEnable();
          if(Interrupt_High_Priority == _timer->priority){
              INTERRUPT_GlobalInterruptHighEnable();
              TIMER1_HighPrioritySet();
          }
          else if(Interrupt_Low_Priority == _timer->priority){
              INTERRUPT_GlobalInterruptLowEnable();
              TIMER1_LowPrioritySet();
          }
          else{
              
          }
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
         
         /* Enable the timer*/
         TIMER1_MODULE_ENABLE();
     }
     return(ret);
}
Std_ReturnType TIMER1_DeInit(const timer1_t *_timer){
    Std_ReturnType ret = E_OK;
     
     if(NULL == _timer){
         ret= E_NOK;
     }
     else{
          TIMER1_MODULE_DISABLE();

        #if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            TIMER1_InterruptDisable();
        #endif
     }
     return(ret);
}
Std_ReturnType TIMER1_Write_value(const timer1_t *_timer, uint16 _value){
    Std_ReturnType ret = E_OK;
     
     if(NULL == _timer){
         ret= E_NOK;
     }
     else{
          TMR1H = (_value) >> 8;
          TMR1L = (uint8)(_value);
     }
     return(ret);
}
Std_ReturnType TIMER1_Read_value(const timer1_t *_timer, uint16 *_value){
    Std_ReturnType ret = E_OK;
     uint8 l_tmr1h = ZERO_INIT, l_tmr1l = ZERO_INIT;
     if((NULL == _timer) || (NULL == _value)){
         ret= E_NOK;
     }
     else{
         l_tmr1l = TMR1L;
         l_tmr1h = TMR1H;
         *_value = (uint16)((l_tmr1h << 8) + l_tmr1l);
     }
     return(ret);
}
void TIMER1_ISR(void){
    TIMER1_InterruptFlagClear();
    TMR1H = (timer1_preload) >> 8;
    TMR1L = (uint8)(timer1_preload);
    if(TIMER1_InterruptHandler){
       TIMER1_InterruptHandler();
        
    }
}
static inline void TIMER1_MODE_Select(const timer1_t *_timer){
    if(TIMER1_TIMER_MODE == _timer->timer1_mode){
        TIMER1_TIMER_MODE_ENABLE();
    }
    else if(TIMER1_COUNTER_MODE == _timer->timer1_mode){
        TIMER1_CONTROL_MODE_ENABLE();
        if(TIMER1_ASYNC_COUNTER_MODE == _timer->timer1_counter_mode){
            TIMER1_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if(TIMER1_SYNC_COUNTER_MODE == _timer->timer1_counter_mode){
            TIMER1_SYNC_COUNTER_MODE_ENABLE();
        }
        else{
        /* Nothing */
        }  
    }
    else{
        /* Nothing */
    }
}