/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F46K20
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include"mcc_generated_files/examples/i2c_master_example.h"
#include"AEUCL_Modules/RTC_DS1307/RTC_DS1307.h"
#include"AEUCL_Modules/EEPROM_24C01C/EEPROM_24C01C.h"
#include"AEUCL_Modules/UART_LoggingDebugData/UART_LoggingDebugData.h"
#include"AEUCL_Modules/TempSensor_TC74/TempSensor_TC74.h"

RTC_DS1307_t GL_RTC_DS1307;
uint8_t U3_REC_DATA, U4_REC_DATA;
volatile uint8_t TempSensor_A7_val = 0;

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // Enable high priority global interrupts
    INTERRUPT_GlobalInterruptHighEnable();

    // Enable low priority global interrupts.
    INTERRUPT_GlobalInterruptLowEnable();
    
    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    UART_LoggingDebugData_Send_Str("System Started\r", 15);
    
     EEPROM_24C01C_Write_Data(0xA6,0x08,3);
     __delay_us(100);
    EEPROM_24C01C_Write_Data(0xA2,0x08,4);
     __delay_us(100);
   
     U3_REC_DATA = EEPROM_24C01C_Read_Data(0xA6,0x08);
     U4_REC_DATA = EEPROM_24C01C_Read_Data(0xA2,0x08);
     
     
    while (1) {
        GL_RTC_DS1307 = RealTimeClock_DS1307();
        RTC_PRINT_STR();
        
        TempSensor_A7_val = TempSensor_TC74_Read_Temp(0x9E);
        I2C_Write1ByteRegister(0x70, 0x00, TempSensor_A7_val);
      
        __delay_ms(500);
    }
}
/**
 End of File
*/