/* 
 * File:   UART_LoggingDebugData.h
 * Author: Naghm Ayman Omar
 *
 * Created on 16 September 2024, 18:39
 */

#ifndef UART_LOGGINGDEBUGDATA_H
#define	UART_LOGGINGDEBUGDATA_H

/*-------------------- INCLUDES Sections ----------------------*/
#include"../../mcc_generated_files/mcc.h"
#include"../../mcc_generated_files/eusart.h"

/*-------------------- SOFTWARE INTERFACES ----------------------*/
void UART_LoggingDebugData_Send_Str(uint8_t *string, uint16_t string_length);
#endif	/* UART_LOGGINGDEBUGDATA_H */

