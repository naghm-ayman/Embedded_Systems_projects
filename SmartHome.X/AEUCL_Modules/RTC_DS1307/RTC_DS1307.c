/* 
 * File:   RTC_DS1307.c
 * Author: Naghm Ayman Omar
 *
 * Created on 16 September 2024, 15:30
 */

#include"RTC_DS1307.h"

static RTC_DS1307_t l_RTC_DS1307;
static uint8_t RTC_Pack[18];

RTC_DS1307_t RealTimeClock_DS1307(void) {
    l_RTC_DS1307.seconds = I2C_Read1ByteRegister(0xD0,0x00);
    l_RTC_DS1307.minutes = I2C_Read1ByteRegister(0xD0,0x01);
    l_RTC_DS1307.hours   = I2C_Read1ByteRegister(0xD0,0x02);
    l_RTC_DS1307.days    = I2C_Read1ByteRegister(0xD0,0x04);
    l_RTC_DS1307.monthe  = I2C_Read1ByteRegister(0xD0,0x05);
    l_RTC_DS1307.years   = I2C_Read1ByteRegister(0xD0,0x06);
    
    return (l_RTC_DS1307);
}

void RTC_PRINT_STR(void){
    RTC_Pack[0] = ((l_RTC_DS1307.days >> 4) + 0x30);
    RTC_Pack[1] = ((l_RTC_DS1307.days & 0x0F) + 0x30);
    RTC_Pack[2] = '-';
    RTC_Pack[3] = ((l_RTC_DS1307.monthe >> 4) + 0x30);
    RTC_Pack[4] = ((l_RTC_DS1307.monthe & 0x0F) + 0x30);
    RTC_Pack[5] = '-';
    RTC_Pack[6] = ((l_RTC_DS1307.years >> 4) + 0x30);
    RTC_Pack[7] = ((l_RTC_DS1307.years & 0x0F) + 0x30);
    
    RTC_Pack[8] = '/';
    
    RTC_Pack[9]  = ((l_RTC_DS1307.hours >> 4) + 0x30);
    RTC_Pack[10] = ((l_RTC_DS1307.hours & 0x0F) + 0x30);
    RTC_Pack[11] = '-';
    RTC_Pack[12] = ((l_RTC_DS1307.minutes >> 4) + 0x30);
    RTC_Pack[13] = ((l_RTC_DS1307.minutes & 0x0F) + 0x30);
    RTC_Pack[14] = '-';
    RTC_Pack[15] = ((l_RTC_DS1307.seconds >> 4) + 0x30);
    RTC_Pack[16] = ((l_RTC_DS1307.seconds & 0x0F) + 0x30);
    
    RTC_Pack[17] = '\r';
    
    UART_LoggingDebugData_Send_Str("Date : ", 8);
    UART_LoggingDebugData_Send_Str(RTC_Pack, 18);
}