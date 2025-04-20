/* 
 * File:   mcal_external_interrupt.c
 * Author: Naghm Ayman Omar
 *
 * Created on 08 July 2024, 14:29
 */

#include"mcal_external_interrupt.h"
static InterruptHandler INT0_InterruptHandler = NULL;
static InterruptHandler INT1_InterruptHandler = NULL;
static InterruptHandler INT2_InterruptHandler = NULL;

static InterruptHandler RB4_InterruptHandler_HIGH = NULL;
static InterruptHandler RB4_InterruptHandler_LOW = NULL;
static InterruptHandler RB5_InterruptHandler_HIGH = NULL;
static InterruptHandler RB5_InterruptHandler_LOW = NULL;
static InterruptHandler RB6_InterruptHandler_HIGH = NULL;
static InterruptHandler RB6_InterruptHandler_LOW = NULL;
static InterruptHandler RB7_InterruptHandler_HIGH = NULL;
static InterruptHandler RB7_InterruptHandler_LOW = NULL;

static Std_ReturnType interrupt_INTx_Enable(const interrupt_INTx_t *inturrpt_obj);
static Std_ReturnType interrupt_INTx_Disable(const interrupt_INTx_t *inturrpt_obj);
static Std_ReturnType interrupt_INTx_Priority_Init(const interrupt_INTx_t *inturrpt_obj);
static Std_ReturnType interrupt_INTx_Edge_Init(const interrupt_INTx_t *inturrpt_obj);
static Std_ReturnType interrupt_INTx_Pin_Init(const interrupt_INTx_t *inturrpt_obj);
static Std_ReturnType interrupt_INTx_Clear_Flag(const interrupt_INTx_t *inturrpt_obj);

static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *inturrpt_obj);


static Std_ReturnType interrupt_RBx_Enable(const interrupt_RBx_t *inturrpt_obj);
static Std_ReturnType interrupt_RBx_Disable(const interrupt_RBx_t *inturrpt_obj);
static Std_ReturnType interrupt_RBx_Priority_Init(const interrupt_RBx_t *inturrpt_obj);
static Std_ReturnType interrupt_RBx_Pin_Init(const interrupt_RBx_t *inturrpt_obj);

Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *inturrpt_obj){
    Std_ReturnType ret = E_NOK;
     
     if(NULL== inturrpt_obj){
         ret= E_NOK;
     }
     else{
          /* Disable the External Interrupt */
         ret = interrupt_INTx_Disable(inturrpt_obj);
        /* Clear flag of the External Interrupt */
         ret |= interrupt_INTx_Clear_Flag(inturrpt_obj);
        /* Configure the External Interrupt Edge */
         ret |= interrupt_INTx_Edge_Init(inturrpt_obj);
        /* Configure the External Interrupt I/O Pin */ 
         ret |= interrupt_INTx_Pin_Init(inturrpt_obj);
        /* Configure the Default External Interrupt Call back   */ 
         ret |= Interrupt_INTx_SetInterruptHandler(inturrpt_obj);
        /* Enable the External Interrupt */
         ret |= interrupt_INTx_Enable(inturrpt_obj);
     }
     return(ret);
}
void INT0_ISR(void){
    /*the INT0 interrupt flag must be cleared*/
     EXT_INT0_InterruptFlagClear();
    /* the code*/
     
    /*Callback Function is called every time this ISR is executed*/
     if(INT0_InterruptHandler){
         INT0_InterruptHandler();
     }
     else{
         /*nothing*/
     }
}
void INT1_ISR(void){
    /*the INT1 interrupt flag must be cleared*/
     EXT_INT1_InterruptFlagClear();
    /* the code*/
     
    /*Callback Function is called every time this ISR is executed*/
     if(INT1_InterruptHandler){
         INT1_InterruptHandler();
     }
     else{
         /*nothing*/
     }
}
void INT2_ISR(void){
    /*the INT2 interrupt flag must be cleared*/
     EXT_INT2_InterruptFlagClear();
    /* the code*/
     
    /*Callback Function is called every time this ISR is executed*/
     if(INT2_InterruptHandler){
         INT2_InterruptHandler();
     }
     else{
         /*nothing*/
     }
}
void RB4_ISR(uint8 RB4_source){
    /*the INT2 interrupt flag must be cleared*/
     EXT_RBx_InterruptFlagClear();
    /* the code*/
     
    /*Callback Function is called every time this ISR is executed*/
     if (0 == RB4_source){
         if(RB4_InterruptHandler_HIGH){
         RB4_InterruptHandler_HIGH();
         }
         else{
         /*nothing*/
         }
     }
     else if (1 == RB4_source){
          if(RB4_InterruptHandler_LOW){
         RB4_InterruptHandler_LOW();
         }
         else{
         /*nothing*/
         }
     }
     else{
         /*nothing*/
     }
}
void RB5_ISR(uint8 RB5_source){
    /*the RB6 interrupt flag must be cleared*/
     EXT_RBx_InterruptFlagClear();
    /* the code*/
     
    /*Callback Function is called every time this ISR is executed*/
    if (0 == RB5_source){
         if(RB5_InterruptHandler_HIGH){
         RB5_InterruptHandler_HIGH();
         }
         else{
         /*nothing*/
         }
     }
     else if (1 == RB5_source){
          if(RB5_InterruptHandler_LOW){
         RB5_InterruptHandler_LOW();
         }
         else{
         /*nothing*/
         }
     }
     else{
         /*nothing*/
     }
}
void RB6_ISR(uint8 RB6_source){
    /*the RB6 interrupt flag must be cleared*/
     EXT_RBx_InterruptFlagClear();
    /* the code*/
     
    /*Callback Function is called every time this ISR is executed*/
     if (0 == RB6_source){
         if(RB6_InterruptHandler_HIGH){
         RB6_InterruptHandler_HIGH();
         }
         else{
         /*nothing*/
         }
     }
     else if (1 == RB6_source){
          if(RB6_InterruptHandler_LOW){
         RB6_InterruptHandler_LOW();
         }
         else{
         /*nothing*/
         }
     }
     else{
         /*nothing*/
     }
}
void RB7_ISR(uint8 RB7_source){
    /*the RB7 interrupt flag must be cleared*/
     EXT_RBx_InterruptFlagClear();
    /* the code*/
     
    /*Callback Function is called every time this ISR is executed*/
     if (0 == RB7_source){
         if(RB7_InterruptHandler_HIGH){
         RB7_InterruptHandler_HIGH();
         }
         else{
         /*nothing*/
         }
     }
     else if (1 == RB7_source){
          if(RB7_InterruptHandler_LOW){
         RB7_InterruptHandler_LOW();
         }
         else{
         /*nothing*/
         }
     }
     else{
         /*nothing*/
     }
     
}
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *inturrpt_obj){
      Std_ReturnType ret = E_OK;
     
     if(NULL == inturrpt_obj){
         ret= E_NOK;
     }
     else{
        ret = interrupt_INTx_Disable(inturrpt_obj);
     }
     return(ret);
}
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *inturrpt_obj){
      Std_ReturnType ret = E_OK;
     
     if(NULL== inturrpt_obj){
         ret= E_NOK;
     }
     else{
         /* this routine clears the interrupt enable of the external interrupt , RBx */
         EXT_RBx_InterruptDisable();
         /* this routine clears the interrupt flag of the external interrupt , RBx */
         EXT_RBx_InterruptFlagClear();
         #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                    INTERRUPT_PriortyLevelEnable();
                 if( Interrupt_Low_Priority == inturrpt_obj->priority){
                     /* this macro will enable low priority global interrupts */
                     INTERRUPT_GlobalInterruptLowEnable();
                     /* this routine sets the RBx External interrupt to be low priority */
                     EXT_RBx_LowPrioritySet();
                 }
                 else if( Interrupt_High_Priority == inturrpt_obj->priority){
                     /* this macro will enable high priority global interrupts */
                     INTERRUPT_GlobalInterruptHighEnable();
                     /* this routine sets the RBx External interrupt to be high priority */
                     EXT_RBx_HighPrioritySet();
                 }
            #else
                 INTERRUPT_GlobalInterruptEnable();
                 INTERRUPT_PeripheralInterruptEnable();  
            #endif 
                    /* this is the initialization of the RBx to be input*/
                 ret = gpio_pin_direction_intialize(&(inturrpt_obj->mcu_pin));
                    /* this is the initialization of the call back function*/
                 switch(inturrpt_obj->mcu_pin.pin){
                     case GPIO_Pin4:
                         RB4_InterruptHandler_HIGH = inturrpt_obj->EXT_InterruptHandler_HIGH;
                         RB4_InterruptHandler_LOW = inturrpt_obj->EXT_InterruptHandler_LOW;
                         break;
                     case GPIO_Pin5:
                         RB5_InterruptHandler_HIGH = inturrpt_obj->EXT_InterruptHandler_HIGH;
                         RB5_InterruptHandler_LOW = inturrpt_obj->EXT_InterruptHandler_LOW;
                         break;
                     case GPIO_Pin6:
                         RB6_InterruptHandler_HIGH = inturrpt_obj->EXT_InterruptHandler_HIGH;
                         RB6_InterruptHandler_LOW = inturrpt_obj->EXT_InterruptHandler_LOW;
                         break;
                     case GPIO_Pin7:
                         RB7_InterruptHandler_HIGH = inturrpt_obj->EXT_InterruptHandler_HIGH;
                         RB7_InterruptHandler_LOW = inturrpt_obj->EXT_InterruptHandler_LOW;
                         break;
                     default :
                         ret = E_NOK;
                          break;
                 }
                EXT_RBx_InterruptEnable();
         
         
     }
     return(ret);
}
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *inturrpt_obj){
      Std_ReturnType ret = E_OK;
     
     if(NULL== inturrpt_obj){
         ret= E_NOK;
     }
     else{
          /* this routine clears the interrupt enable of the external interrupt , RBx */
         EXT_RBx_InterruptDisable();
         /* this routine clears the interrupt flag of the external interrupt , RBx */
         EXT_RBx_InterruptFlagClear();
     }
     return(ret);
}



static Std_ReturnType interrupt_INTx_Enable(const interrupt_INTx_t *inturrpt_obj){
      Std_ReturnType ret = E_OK;
     
     if(NULL== inturrpt_obj){
         ret= E_NOK;
     }
     else{
         switch(inturrpt_obj->source){
             case Interrupt_External_INT0:
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                 INTERRUPT_GlobalInterruptHighEnable();
            #else
                   INTERRUPT_GlobalInterruptEnable();
                 INTERRUPT_PeripheralInterruptEnable();  
            #endif           
                 EXT_INT0_InterruptEnable();
                 break;
            case Interrupt_External_INT1:
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                    INTERRUPT_PriortyLevelEnable();
                   if( Interrupt_Low_Priority == inturrpt_obj->priority){
                     INTERRUPT_GlobalInterruptLowEnable();
                 }
                 else if( Interrupt_High_Priority == inturrpt_obj->priority){
                     INTERRUPT_GlobalInterruptHighEnable();
                 }
            #else
                   INTERRUPT_GlobalInterruptEnable();
                 INTERRUPT_PeripheralInterruptEnable();  
            #endif 
                EXT_INT1_InterruptEnable();
                 break;
            case Interrupt_External_INT2:
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                    INTERRUPT_PriortyLevelEnable();
                 if( Interrupt_Low_Priority == inturrpt_obj->priority){
                     INTERRUPT_GlobalInterruptLowEnable();
                 }
                 else if( Interrupt_High_Priority == inturrpt_obj->priority){
                     INTERRUPT_GlobalInterruptHighEnable();
                 }
            #else
                 INTERRUPT_GlobalInterruptEnable();
                 INTERRUPT_PeripheralInterruptEnable();  
            #endif 
                EXT_INT2_InterruptEnable();
                 break;
            default: ret = E_NOK;
                 break;
         }
        
     }
     return(ret);
}
static Std_ReturnType interrupt_INTx_Disable(const interrupt_INTx_t *inturrpt_obj){
      Std_ReturnType ret = E_OK;
     
     if(NULL== inturrpt_obj){
         ret= E_NOK;
     }
     else{
            switch(inturrpt_obj->source){
             case Interrupt_External_INT0:
                 EXT_INT0_InterruptDisable();
                 break;
            case Interrupt_External_INT1:
                EXT_INT1_InterruptDisable();
                 break;
            case Interrupt_External_INT2:
                EXT_INT2_InterruptDisable();
                 break;
             default: ret = E_NOK;
                 break;
         }
        
     }
     return(ret);
}

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType interrupt_INTx_Priority_Init(const interrupt_INTx_t *inturrpt_obj){
      Std_ReturnType ret = E_OK;
     
     if(NULL== inturrpt_obj){
         ret= E_NOK;
     }
     else{
         switch(inturrpt_obj->source){
             case Interrupt_External_INT1:
                 if( Interrupt_Low_Priority == inturrpt_obj->priority){
                     EXT_INT1_LowPrioritySet();
                 }
                 else if( Interrupt_High_Priority == inturrpt_obj->priority){
                     EXT_INT1_HighPrioritySet();
                 }
                 else {/* Nothing*/}
                 break;
             case Interrupt_External_INT2:
                   if( Interrupt_Low_Priority == inturrpt_obj->priority){
                     EXT_INT2_LowPrioritySet();
                 }
                 else if( Interrupt_High_Priority == inturrpt_obj->priority){
                     EXT_INT2_HighPrioritySet();
                 }
                 else {/* Nothing*/}
                 break;
                 default: ret = E_NOK;
                 break;
         }
        
     }
     return(ret);
}
#endif

static Std_ReturnType interrupt_INTx_Edge_Init(const interrupt_INTx_t *inturrpt_obj){
      Std_ReturnType ret = E_OK;
     
     if(NULL== inturrpt_obj){
         ret= E_NOK;
     }
     else{
         switch(inturrpt_obj->source){
             case Interrupt_External_INT0:
                 if( Interrupt_Falling_Edge == inturrpt_obj->edge){
                     EXT_INT0_FallingEdge();
                 }
                 else if( Interrupt_Rising_Edge == inturrpt_obj->edge){
                     EXT_INT0_RisingEdge();
                 }
                 else {/* Nothing*/}
                 break;
             case Interrupt_External_INT1:
                   if( Interrupt_Falling_Edge == inturrpt_obj->edge){
                     EXT_INT1_FallingEdge();
                 }
                 else if( Interrupt_Rising_Edge == inturrpt_obj->edge){
                     EXT_INT1_RisingEdge();
                 }
                 else {/* Nothing*/}
                 break;
             case Interrupt_External_INT2:
                   if( Interrupt_Falling_Edge == inturrpt_obj->edge){
                     EXT_INT2_FallingEdge();
                 }
                 else if( Interrupt_Rising_Edge == inturrpt_obj->edge){
                     EXT_INT2_RisingEdge();
                 }
                 else {/* Nothing*/}
                 break;
             default: ret = E_NOK;
                 break;
         }
        
     }
     return(ret);
}
static Std_ReturnType interrupt_INTx_Pin_Init(const interrupt_INTx_t *inturrpt_obj){
      Std_ReturnType ret = E_OK;
     
     if(NULL== inturrpt_obj){
         ret= E_NOK;
     }
     else{
         ret = gpio_pin_direction_intialize(&(inturrpt_obj->mcu_pin));
     }
     return(ret);
}
static Std_ReturnType interrupt_INTx_Clear_Flag(const interrupt_INTx_t *inturrpt_obj){
      Std_ReturnType ret = E_OK;
     
     if(NULL== inturrpt_obj){
         ret= E_NOK;
     }
     else{
        switch(inturrpt_obj->source){
             case Interrupt_External_INT0:
                 EXT_INT0_InterruptFlagClear();
                 break;
            case Interrupt_External_INT1:
                EXT_INT1_InterruptFlagClear();
                 break;
            case Interrupt_External_INT2:
                EXT_INT2_InterruptFlagClear();
                 break;
            default: ret = E_NOK;
                 break;
         }
     }
     return(ret);
}

static Std_ReturnType interrupt_RBx_Enable(const interrupt_RBx_t *inturrpt_obj){
     Std_ReturnType ret = E_OK;
     
     if(NULL== inturrpt_obj){
         ret= E_NOK;
     }
     else{
        
     }
     return(ret);
}
static Std_ReturnType interrupt_RBx_Disable(const interrupt_RBx_t *inturrpt_obj){
     Std_ReturnType ret = E_OK;
     
     if(NULL== inturrpt_obj){
         ret= E_NOK;
     }
     else{
        
     }
     return(ret);
}
static Std_ReturnType interrupt_RBx_Priority_Init(const interrupt_RBx_t *inturrpt_obj){
     Std_ReturnType ret = E_OK;
     
     if(NULL== inturrpt_obj){
         ret= E_NOK;
     }
     else{
        
     }
     return(ret);
}
static Std_ReturnType interrupt_RBx_Pin_Init(const interrupt_RBx_t *inturrpt_obj){
     Std_ReturnType ret = E_OK;
     
     if(NULL == inturrpt_obj){
         ret = E_NOK;
     }
     else{
         
     }
     return(ret);
}
static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void)){
      Std_ReturnType ret = E_OK;
     
     if(NULL == InterruptHandler){
         ret = E_NOK;
     }
     else{
        INT0_InterruptHandler = InterruptHandler;
     }
     return(ret);
}
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void)){
      Std_ReturnType ret = E_OK;
     
     if(NULL == InterruptHandler){
         ret = E_NOK;
     }
     else{
        INT1_InterruptHandler = InterruptHandler;
     }
     return(ret);
}
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void)){
      Std_ReturnType ret = E_OK;
     
     if(NULL == InterruptHandler){
         ret = E_NOK;
     }
     else{
        INT2_InterruptHandler = InterruptHandler;
     }
     return(ret);
}
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *inturrpt_obj){
       Std_ReturnType ret = E_OK;
     
     if(NULL== inturrpt_obj){
         ret= E_NOK;
     }
     else{
        switch(inturrpt_obj->source){
             case Interrupt_External_INT0:
                 INT0_SetInterruptHandler(inturrpt_obj->EXT_InterruptHandler);
                 break;
            case Interrupt_External_INT1:
                INT1_SetInterruptHandler(inturrpt_obj->EXT_InterruptHandler);
                 break;
            case Interrupt_External_INT2:
                ret = INT2_SetInterruptHandler(inturrpt_obj->EXT_InterruptHandler);
                 break;
            default: ret = E_NOK;
                 break;
         }
     }
     return(ret);
}