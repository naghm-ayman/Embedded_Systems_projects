/* 
 * File:   hal_usart.h
 * Author: Naghm Ayman Omar
 *
 * Created on 02 August 2024, 14:54
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/* --------------------- section of INCLUDES ---------------------*/
#include"pic18f4620.h"
#include"../mcal_std_types.h"
#include"../../MCAL_layer/GPIO/hal_gpio.h"
#include"../../MCAL_layer/Interrupt/mcal_internal_interrupt.h"
#include"hal_usart_cfg.h"
/*--------------------- section of MACRO DECLARATIONS --------------------- */
/* Enable / Disable EUSART Module  */
#define EUSART_MODULE_ENABLE   1
#define EUSART_MODULE_DISABLE  0
/* Selecting EUSART working mode */
#define EUSART_SYNCHRONOUS_MODE   1
#define EUSART_ASYNCHRONOUS_MODE  0
/* Baud Rate Generator Asynchronous speed mode */
#define EUSART_ASYNCRONOUS_HIGH_SPEED 1
#define EUSART_ASYNCRONOUS_LOW_SPEED  0
/* Baud Rate Generator Asynchronous register size */
#define EUSART_16BIT_BAUDRATE_GEN 1
#define EUSART_8BIT_BAUDRATE_GEN  0

/* EUSART Transmit mode */
#define EUSART_ASYNCHRONOUS_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_TX_DISABLE  0
/* EUSART Transmit Interrupt mode */
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE  0
/* EUSART 9Bit Transmit mode */
#define EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE  0

/* EUSART Receiver mode */
#define EUSART_ASYNCHRONOUS_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_RX_DISABLE  0
/* EUSART Receiver Interrupt mode */
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE  0
/* EUSART 9Bit Receiver mode */
#define EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE  0
/* EUSART Framing Error */
#define EUSART_FRAMING_ERROR_DETECTED  1
#define EUSART_FRAMING_ERROR_CLEARED   0
/* EUSART OverRun Error */
#define EUSART_OVERRUN_ERROR_DETECTED  1
#define EUSART_OVERRUN_ERROR_CLEARED   0
/*--------------------- section of MACRO FUNCTIONS DECLARATIONS --------------------- */

/*--------------------- section of DATA TYPE DECLARATIONS --------------------- */
typedef enum{
    BuadRate_ASYNC_8BIT_LOW_SPEED,
    BuadRate_ASYNC_8BIT_HIGH_SPEED,
    BuadRate_ASYNC_16BIT_LOW_SPEED,
    BuadRate_ASYNC_16BIT_HIGH_SPEED,
    BuadRate_SYNC_8BIT,
    BuadRate_SYNC_16BIT
}BuadRate_gen_t;

typedef struct{
    uint8 usart_tx_reserved : 5;
    uint8 usart_tx_enable : 1;
    uint8 usart_tx_interrupt_enable : 1;
    uint8 usart_tx_9bit_enable : 1;
    interrupt_priority_cfg usart_tx_priority;
}usart_tx_cfg_t;

typedef struct{
    uint8 usart_rx_reserved : 5;
    uint8 usart_rx_enable : 1;
    uint8 usart_rx_interrupt_enable : 1;
    uint8 usart_rx_9bit_enable : 1;
    interrupt_priority_cfg usart_rx_priority;
}usart_rx_cfg_t;

typedef union{
    struct{
    uint8 usart_reserved : 6;
    uint8 usart_ferr : 1;
    uint8 usart_oerr : 1;
};
     uint8 status;
}usart_error_state_t;

typedef struct{
    uint32 baudrate;
    BuadRate_gen_t baudrate_gen_config;
    usart_tx_cfg_t usart_tx_cfg;
    usart_rx_cfg_t usart_rx_cfg;
    usart_error_state_t error_state;
    void (*EUSART_TX_InterruptHandler)(void);
    void (*EUSART_RX_InterruptHandler)(void);
    void (*EUSART_FramingErrorHandler)(void);
    void (*EUSART_OverRunErrorHandler)(void);
}usart_t;
/*--------------------- section of SOFTWARE INTERFACES DECLARATIONS --------------------- */ 
Std_ReturnType EUSART_ASYNC_Init(const usart_t *_eusart);
Std_ReturnType EUSART_ASYNC_DeInit(const usart_t *_eusart);

Std_ReturnType EUSART_ASYNC_ReadByte_Blocking( uint8 *_value);
Std_ReturnType EUSART_ASYNC_ReadByte_NonBlocking( uint8 *_value);
Std_ReturnType EUSART_ASYNC_RX_Restart(void);

Std_ReturnType EUSART_ASYNC_WriteByte_Blocking(uint8 _value);
Std_ReturnType EUSART_ASYNC_WriteString_Blocking(uint8 *_value, uint16 str_len);
#endif	/* HAL_USART_H */

