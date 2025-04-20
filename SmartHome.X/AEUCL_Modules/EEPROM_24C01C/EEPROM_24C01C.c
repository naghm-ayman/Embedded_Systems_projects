/* 
 * File:   EEPROM_24C01C.c
 * Author: Naghm Ayman Omar
 *
 * Created on 16 September 2024, 18:27
 */

#include <pic18.h>
#include"EEPROM_24C01C.h"

void EEPROM_24C01C_Write_Data(i2c_address_t EEPROM_Add, i2c_address_t Data_Add, uint8_t data){
    I2C_Write1ByteRegister(EEPROM_Add, Data_Add, data);
}

uint8_t EEPROM_24C01C_Read_Data(i2c_address_t EEPROM_Add,i2c_address_t Data_Add){
    uint8_t Rec_Data = 0;
    Rec_Data = I2C_Read1ByteRegister(EEPROM_Add, Data_Add);
    
    return(Rec_Data);
}