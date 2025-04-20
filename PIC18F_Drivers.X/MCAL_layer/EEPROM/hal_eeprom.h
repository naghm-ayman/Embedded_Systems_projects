/* 
 * File:   hal_eeprom.h
 * Author: Naghm Ayman Omar
 *
 * Created on 16 July 2024, 15:47
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/*section of INCLUDES */
#include "pic18f4620.h"
#include"../mcal_std_types.h"
#include"../../MCAL_layer/Interrupt/mcal_internal_interrupt.h"

/*section of MACRO DECLARATIONS */
/* Flash program/EEPROM data memory select*/
#define ACCESS_FLASH_PROGRAM_MEMORY      1
#define ACCESS_EEPROM_PROGRAM_MEMORY     0
/* Flash program/EEPROM data memory/Configuration Bits select*/
#define ACCESS_CONFIG_REGISTERS          1
#define ACCESS_FLASH_EEPROM_MEMORY       0
/* Flash program/EEPROM data memory Write Enable*/
#define ALLOW_WRITE_CYCLE_FLASH_EEPROM   1
#define INHABIT_WRITE_CYCLE_FLASH_EEPROM 0
/* Write Control */
#define INTIATE_DATA_EEPROM_WRITE_ERASE      1
#define INTIATE_DATA_EEPROM_WRITE_COMPLETED  0
/* Read Control */
#define INTIATE_DATA_EEPROM_READ        1
/*section of MACRO FUNCTIONS DECLARATIONS */

/*section of SOFTWARE INTERFACES DECLARATIONS*/
Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData);
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData);

#endif	/* HAL_EEPROM_H */

