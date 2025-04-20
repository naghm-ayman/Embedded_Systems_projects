/* 
 * File:   EEPROM_24C01C.h
 * Author: Naghm Ayman Omar
 *
 * Created on 16 September 2024, 18:27
 */

#ifndef EEPROM_24C01C_H
#define	EEPROM_24C01C_H
/*-------------------- INCLUDES Sections ----------------------*/
#include"../../mcc_generated_files/mcc.h"
#include"../../mcc_generated_files/examples/i2c_master_example.h"


/*-------------------- SOFTWARE INTERFACES ----------------------*/
void EEPROM_24C01C_Write_Data(i2c_address_t EEPROM_Add, i2c_address_t Data_Add, uint8_t data);
uint8_t EEPROM_24C01C_Read_Data(i2c_address_t EEPROM_Add,i2c_address_t Data_Add);


#endif	/* EEPROM_24C01C_H */

