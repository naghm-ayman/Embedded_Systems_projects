
/*
 * File:   USART.h
 * Author: Naghm Ayman Omar
 *
 * Created on 29 October 2024, 17:05
 */
#ifndef MCAL_USART_USART_H_
#define MCAL_USART_USART_H_

#include "avr/io.h"
#include "avr/interrupt.h"
#include "USART_config.h"
#include "../STD_Types.h"
#include <stdio.h>

void UART_Init(void);

void UART_SendByte(uint8_t data);
void UART_SendString(sint8_t *str);
uint8_t UART_ReceiveByte(void);
void UART_ReceiveString(uint8_t *str, uint8_t maxLength);
uint8_t UART_Receive_NoBlock(uint8_t *pdata);

void UART_SendHex(uint32 Num);

void UART_RX_InterruptEnable(void);
void UART_RX_InterruptDisable(void);

void UART_TX_InterruptEnable(void);
void UART_TX_InterruptDisable(void);

void UART_RX_SetCallBack(void (*LocalFptr)(void));
void UART_TX_SetCallBack(void (*LocalFptr)(void));

void UART_SendByteNoBlock(uint8_t data);
uint8_t UART_ReceiveByteNoBlock(void);

void UART_ReceiveWord(uint16_t *value);
#endif /* MCAL_USART_USART_H_ */
