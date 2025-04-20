/* 
 * File:   hal_usart.c
 * Author: Naghm Ayman Omar
 *
 * Created on 02 August 2024, 14:54
 */

#include"hal_usart.h"
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void (*EUSART_TX_InterruptHandler)(void) = NULL;
#endif

#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void (*EUSART_RX_InterruptHandler)(void) = NULL;
    static void (*EUSART_FramingError_InterruptHandler)(void) = NULL;
    static void (*EUSART_OverRunError_InterruptHandler)(void) = NULL;
#endif

static void EUSART_Baud_Rate_Calculation(const usart_t *_eusart);
static void EUSART_ASYNC_TX_INIT(const usart_t *_eusart);
static void EUSART_ASYNC_RX_INIT(const usart_t *_eusart);
Std_ReturnType EUSART_ASYNC_Init(const usart_t *_eusart){
    Std_ReturnType ret = E_OK;
     
     if(NULL == _eusart){
         ret= E_NOK;
     }
     else{
         /* Disable the EUSART */
         RCSTAbits.SPEN = EUSART_MODULE_DISABLE;
         
         TRISCbits.RC6 = 1;
         TRISCbits.RC7 = 1;
          EUSART_Baud_Rate_Calculation(_eusart);
          EUSART_ASYNC_TX_INIT(_eusart);
          EUSART_ASYNC_RX_INIT(_eusart);
         /* Enable the EUSART */
          RCSTAbits.SPEN = EUSART_MODULE_ENABLE;
          
     }
     return(ret);
    
}
Std_ReturnType EUSART_ASYNC_DeInit(const usart_t *_eusart){
    Std_ReturnType ret = E_OK;
     
     if(NULL == _eusart){
         ret= E_NOK;
     }
     else{
          /* Disable the EUSART */
         RCSTAbits.SPEN = EUSART_MODULE_DISABLE;
     }
     return(ret);
}
Std_ReturnType EUSART_ASYNC_ReadByte_Blocking( uint8  *_value){
    Std_ReturnType ret = E_OK;
         while (!PIR1bits.RCIF);
         *_value = RCREG;
     return(ret);
}
Std_ReturnType EUSART_ASYNC_ReadByte_NonBlocking( uint8 *_value) {
    Std_ReturnType ret = E_OK;

    if (NULL == _value) {
        ret = E_NOK;
    } 
    else {
        if (1 == PIR1bits.RCIF) {
            *_value = RCREG;
            ret = E_OK;
        } else {
            ret = E_NOK;
        }
        return (ret);
}
}
Std_ReturnType EUSART_ASYNC_RX_Restart(void){
    Std_ReturnType ret = E_OK;
    RCSTAbits.CREN = ZERO_INIT; /* Disable the receiver */
    RCSTAbits.CREN = 1;         /* Enable the receiver */
     return (ret);
}
Std_ReturnType EUSART_ASYNC_WriteByte_Blocking(uint8 _value){
    Std_ReturnType ret = E_OK;
    while (!TXSTAbits.TRMT);
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    EUSART_TX_InterruptEnable();
#endif
    TXREG = _value;
    return (ret);
}
Std_ReturnType EUSART_ASYNC_WriteString_Blocking(uint8 *_value, uint16 str_len){
    Std_ReturnType ret = E_OK;    
     if(NULL == _value){
         ret= E_NOK;
     }
     else{
          uint16 char_counter = ZERO_INIT;
          for(char_counter = ZERO_INIT; char_counter < str_len; char_counter++){
              ret = EUSART_ASYNC_WriteByte_Blocking(_value[char_counter]);
          }
     }
     return(ret);
    
}

static void EUSART_Baud_Rate_Calculation(const usart_t *_eusart){
    float BaudRate_temp = ZERO_INIT;
    switch(_eusart->baudrate_gen_config ) {
        case BuadRate_ASYNC_8BIT_LOW_SPEED:
             TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
             TXSTAbits.BRGH = EUSART_ASYNCRONOUS_LOW_SPEED;
             BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
             BaudRate_temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 64) - 1;
            break;
        case BuadRate_ASYNC_8BIT_HIGH_SPEED:
             TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
             TXSTAbits.BRGH = EUSART_ASYNCRONOUS_HIGH_SPEED;
             BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
             BaudRate_temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 16) - 1;
            break;
        case BuadRate_ASYNC_16BIT_LOW_SPEED:
             TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
             TXSTAbits.BRGH = EUSART_ASYNCRONOUS_LOW_SPEED;
             BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
             BaudRate_temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 16) - 1;
            break;
        case BuadRate_ASYNC_16BIT_HIGH_SPEED:
             TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
             TXSTAbits.BRGH = EUSART_ASYNCRONOUS_HIGH_SPEED;
             BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
             BaudRate_temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1;
            break;
        case BuadRate_SYNC_8BIT:
             TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
             BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
             BaudRate_temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1;
            break;
        case BuadRate_SYNC_16BIT:
             TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
             BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
             BaudRate_temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1;
            break;
        default: /* Nothing */
            break;
    }
    SPBRG = (uint8)((uint32)BaudRate_temp);
    SPBRGH = (uint8)(((uint32)BaudRate_temp) >> 8);
}
static void EUSART_ASYNC_TX_INIT(const usart_t *_eusart) {
    /* EUSART Transmit ENABLE */
    if(EUSART_ASYNCHRONOUS_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_enable){
        TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_ENABLE;
        EUSART_TX_InterruptHandler = _eusart->EUSART_TX_InterruptHandler;
         /*Configure the Interrupt */
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
         EUSART_TX_InterruptEnable();         
  /*Configure the Interrupt Priority Levels */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
           INTERRUPT_PriortyLevelEnable();
          if(Interrupt_High_Priority == _eusart->usart_tx_cfg.usart_tx_priority){
              INTERRUPT_GlobalInterruptHighEnable();
              EUSART_TX_HighPrioritySet();
          }
          else if(Interrupt_Low_Priority == _eusart->usart_tx_cfg.usart_tx_priority){
              INTERRUPT_GlobalInterruptLowEnable();
              EUSART_TX_LowPrioritySet();
          }
          else{
              
          }
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        /* EUSART Transmit Interrupt Configuration */
        if(EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_interrupt_enable){
            PIE1bits.TXIE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE;
        }
        else if(EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE == _eusart->usart_tx_cfg.usart_tx_interrupt_enable){
            PIE1bits.TXIE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE;
        }
        else{
            /* Nothing */
        }
        
        /* EUSART 9-BIT Transmit Configuration */
         if(EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_9bit_enable){
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE;
        }
        else if(EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE == _eusart->usart_tx_cfg.usart_tx_9bit_enable){
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE;
        }
        else{
            /* Nothing */
        }
    }
    else{
        /* Nothing */
    }
}
static void EUSART_ASYNC_RX_INIT(const usart_t *_eusart) {
     /* EUSART Receive ENABLE */
    if(EUSART_ASYNCHRONOUS_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_enable){
        RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE;
        EUSART_RX_InterruptHandler = _eusart->EUSART_RX_InterruptHandler;
        EUSART_FramingError_InterruptHandler = _eusart->EUSART_FramingErrorHandler;
        EUSART_OverRunError_InterruptHandler = _eusart->EUSART_OverRunErrorHandler;
                 /*Configure the Interrupt */
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
         EUSART_RX_InterruptEnable();         
  /*Configure the Interrupt Priority Levels */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
           INTERRUPT_PriortyLevelEnable();
          if(Interrupt_High_Priority == _eusart->usart_rx_cfg.usart_rx_priority){
              INTERRUPT_GlobalInterruptHighEnable();
              EUSART_RX_HighPrioritySet();
          }
          else if(Interrupt_Low_Priority == _eusart->usart_rx_cfg.usart_rx_priority){
              INTERRUPT_GlobalInterruptLowEnable();
              EUSART_RX_LowPrioritySet();
          }
          else{
              
          }
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        /* EUSART Receive Interrupt Configuration */
        if(EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_interrupt_enable){
            PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE;
        }
        else if(EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE == _eusart->usart_rx_cfg.usart_rx_interrupt_enable){
            PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE;
        }
        else{
            /* Nothing */
        }
        
        /* EUSART 9-BIT Receive Configuration */
         if(EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_9bit_enable){
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE;
        }
        else if(EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE == _eusart->usart_rx_cfg.usart_rx_9bit_enable){
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE;
        }
        else{
            /* Nothing */
        }
    }
    else{
        /* Nothing */
    }
}

void EUSART_Tx_ISR(void){
    EUSART_TX_InterruptDisable();
    if(EUSART_TX_InterruptHandler){
       EUSART_TX_InterruptHandler(); 
    }
    else{
        /* Nothing */
    }
}
void EUSART_Rx_ISR(void){
    if(EUSART_RX_InterruptHandler){
       EUSART_RX_InterruptHandler(); 
    }
    else{/* Nothing */}
    if(EUSART_FramingError_InterruptHandler){
       EUSART_FramingError_InterruptHandler(); 
    }
    else{/* Nothing */}   
    if(EUSART_OverRunError_InterruptHandler){
       EUSART_OverRunError_InterruptHandler(); 
    }
    else{/* Nothing */}  
}