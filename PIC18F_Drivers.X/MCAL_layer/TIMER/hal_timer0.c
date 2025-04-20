/* 
 * File:   hal_timer0.c
 * Author: Naghm Ayman Omar
 *
 * Created on 23 July 2024, 14:10
 */

#include"hal_timer0.h"

#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TIMER0_InterruptHandler)(void) = NULL;
#endif

static uint16 timer0_preload = ZERO_INIT;
static inline void TIMER0_Prescaler_config(const timer0_t *_timer);
static inline void TIMER0_MODE_Select(const timer0_t *_timer);
static inline void TIMER0_REGISTSER_SIZE_config(const timer0_t *_timer);

Std_ReturnType TIMER0_Init(const timer0_t *_timer){
    Std_ReturnType ret = E_OK;
     
     if(NULL == _timer){
         ret= E_NOK;
     }
     else{
         /* Disable the timer */
        TIMER0_MODULE_DISABLE();
       
        TIMER0_Prescaler_config(_timer);
        TIMER0_MODE_Select(_timer);
        TIMER0_REGISTSER_SIZE_config(_timer);
        TMR0H = (_timer->timer0_preload_value) >> 8;
        TMR0L = (uint8)(_timer->timer0_preload_value);
        timer0_preload = _timer->timer0_preload_value;
        /*Configure the Interrupt */
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
           
            TIMER0_InterruptEnable();
            TIMER0_InterruptFlagClear();
            TIMER0_InterruptHandler = _timer->TIMER0_InterruptHandler;
        /*Configure the Interrupt Priority Levels */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PriortyLevelEnable();
          if(Interrupt_High_Priority == _timer->priority){
              INTERRUPT_GlobalInterruptHighEnable();
              TIMER0_HighPrioritySet();
          }
          else if(Interrupt_Low_Priority == _timer->priority){
              INTERRUPT_GlobalInterruptLowEnable();
              TIMER0_LowPrioritySet();
          }
          else{
              
          }
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
             
#endif
#endif
       /* Enable the timer*/
         TIMER0_MODULE_ENABLE();
     }
     return(ret);
}
Std_ReturnType TIMER0_DeInit(const timer0_t *_timer){
    Std_ReturnType ret = E_OK;
     
     if(NULL == _timer){
         ret= E_NOK;
     }
     else{
          TIMER0_MODULE_DISABLE();

        #if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            TIMER0_InterruptDisable();
        #endif
     }
     return(ret);
}
Std_ReturnType TIMER0_Write_value(const timer0_t *_timer, uint16 _value){
    Std_ReturnType ret = E_OK;
     
     if(NULL == _timer){
         ret= E_NOK;
     }
     else{
        TMR0H = (_value) >> 8;
        TMR0L = (uint8)(_value);
     }
     return(ret);
}
Std_ReturnType TIMER0_Read_value(const timer0_t *_timer, uint16 *_value){
    Std_ReturnType ret = E_OK;
    uint8 l_tmr0h = ZERO_INIT, l_tmr0l = ZERO_INIT;
     if((NULL == _timer)||(NULL == _value)){
         ret= E_NOK;
     }
     else{
         l_tmr0l = TMR0L;
         l_tmr0h = TMR0H;
         *_value = (uint16)((l_tmr0h << 8) + l_tmr0l);
        
     }
     return(ret);
    
}
void TIMER0_ISR(void){
    TIMER0_InterruptFlagClear();
    TMR0H = (timer0_preload) >> 8;
    TMR0L = (uint8)(timer0_preload);
    if(TIMER0_InterruptHandler){
       TIMER0_InterruptHandler();
        
    }
}
static inline void TIMER0_Prescaler_config(const timer0_t *_timer){
    if(TIMER0_PRESCALER_ENABLE_CFG == _timer->prescaler_enable){
        TIMER0_PRESCALER_ENABLE();
        T0CONbits.T0PS = _timer->prescaler_value;
    }
    else if(TIMER0_PRESCALER_DISABLE_CFG == _timer->prescaler_enable){
        TIMER0_PRESCALER_DISABLE();
    }
    else{
        /* Nothing */
    }
}
static inline void TIMER0_MODE_Select(const timer0_t *_timer){
    if(TIMER0_TIMER_MODE_ENABLE_CFG == _timer->timer0_mode){
       TIMER0_TIMER_MODE_ENABLE();
    }
    else if(TIMER0_COUNTER_MODE_ENABLE_CFG == _timer->timer0_mode){
        TIMER0_CONTROL_MODE_ENABLE();
        if(TIMER0_RISING_EDGE_ENABLE_CFG == _timer->timer0_counter_edge){
            TIMER0_RISING_EDGE_ENABLE();
        }
        else if(TIMER0_FALLING_EDGE_ENABLE_CFG == _timer->timer0_counter_edge){
            TIMER0_FALLING_EDGE_ENABLE();
        }
        else{
        /* Nothing */
        }  
    }
    else{
        /* Nothing */
    }
}
static inline void TIMER0_REGISTSER_SIZE_config(const timer0_t *_timer){
    if(TIMER0_8_BITS_REGISTER_MODE == _timer->timer0_register_size){
       TIMER0_8_BITS_REGISTER_ENABLE();
    }
    else if(TIMER0_16_BITS_REGISTER_MODE == _timer->timer0_register_size){
        TIMER0_16_BITS_REGISTER_ENABLE();
    }
    else{
        /* Nothing */
    }
}