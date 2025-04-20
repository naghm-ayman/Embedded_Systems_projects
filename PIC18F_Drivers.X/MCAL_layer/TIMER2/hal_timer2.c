/* 
 * File:   hal_timer2.c
 * Author: Naghm Ayman Omar
 *
 * Created on 26 July 2024, 14:32
 */

#include"hal_timer2.h"
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TIMER2_InterruptHandler)(void) = NULL;
#endif

static uint8 timer2_preload = ZERO_INIT;


Std_ReturnType TIMER2_Init(const timer2_t *_timer){
     Std_ReturnType ret = E_OK;
     
     if(NULL == _timer){
         ret= E_NOK;
     }
     else{
         /* Disable the timer */
        TIMER2_MODULE_DISABLE();
        TIMER2_PRESCALER_SELSCT(_timer->timer2_prescaler_value);
        TIMER2_POSTSCALER_SELSCT(_timer->timer2_postscaler_value);
        TMR2 = _timer->timer2_preload_value;
        timer2_preload = _timer->timer2_preload_value;
        
         /*Configure the Interrupt */
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
         TIMER1_InterruptEnable();
         TIMER1_InterruptFlagClear();
         TIMER2_InterruptHandler = _timer->TIMER2_InterruptHandler;
  /*Configure the Interrupt Priority Levels */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
           INTERRUPT_PriortyLevelEnable();
          if(Interrupt_High_Priority == _timer->priority){
              INTERRUPT_GlobalInterruptHighEnable();
              TIMER2_HighPrioritySet();
          }
          else if(Interrupt_Low_Priority == _timer->priority){
              INTERRUPT_GlobalInterruptLowEnable();
              TIMER2_LowPrioritySet();
          }
          else{
              
          }
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
         
         /* Enable the timer*/
         TIMER2_MODULE_ENABLE();
     }
     return(ret);
}
Std_ReturnType TIMER2_DeInit(const timer2_t *_timer){
    Std_ReturnType ret = E_OK;
     
     if(NULL == _timer){
         ret= E_NOK;
     }
     else{
            TIMER2_MODULE_DISABLE();

#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            TIMER2_InterruptDisable();
#endif
     }
     return(ret);
}
Std_ReturnType TIMER2_Write_value(const timer2_t *_timer, uint8 _value){
     Std_ReturnType ret = E_OK;
     
     if(NULL == _timer){
         ret= E_NOK;
     }
     else{
          TMR2 = _value;
     }
     return(ret);
}
Std_ReturnType TIMER2_Read_value(const timer2_t *_timer, uint8 *_value){
    Std_ReturnType ret = E_OK;
     
     if((NULL == _timer)||(NULL == _value)){
         ret= E_NOK;
     }
     else{
          *_value = TMR2;
     }
     return(ret);
}

void TIMER2_ISR(void){
    TIMER2_InterruptFlagClear();
    TMR2 = timer2_preload;
    if(TIMER2_InterruptHandler){
       TIMER2_InterruptHandler();
        
    }
}