/* 
 * File:   RTC_DS1307.h
 * Author: Naghm Ayman Omar
 *
 * Created on 16 September 2024, 15:30
 */

#ifndef RTC_DS1307_H
#define	RTC_DS1307_H

/*-------------------- INCLUDES Sections ----------------------*/
#include"../../mcc_generated_files/mcc.h"
#include"../../mcc_generated_files/examples/i2c_master_example.h"
#include"../UART_LoggingDebugData/UART_LoggingDebugData.h"
/*-------------------- DATATYPES DECLARATIONS ----------------------*/

typedef struct{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t days;
    uint8_t monthe;
    uint8_t years;
}RTC_DS1307_t;
/*-------------------- SOFTWARE INTERFACES ----------------------*/
RTC_DS1307_t RealTimeClock_DS1307(void);
void RTC_PRINT_STR(void);
#endif	/* RTC_DS1307_H */

