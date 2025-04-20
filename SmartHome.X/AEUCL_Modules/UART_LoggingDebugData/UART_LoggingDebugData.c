/* 
 * File:   UART_LoggingDebugData.c
 * Author: Naghm Ayman Omar
 *
 * Created on 16 September 2024, 18:39
 */
#include"UART_LoggingDebugData.h"

void UART_LoggingDebugData_Send_Str(uint8_t *string, uint16_t string_length){
    uint16_t l_uart_string = 0;
    for(l_uart_string = 0; l_uart_string < string_length; l_uart_string++ ){
        EUSART_Write(*string++);
    }
}