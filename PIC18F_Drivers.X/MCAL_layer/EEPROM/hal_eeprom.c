
/* 
 * File:   hal_eeprom.c
 * Author: Naghm Ayman Omar
 *
 * Created on 16 July 2024, 15:47
 */

#include"hal_eeprom.h"

Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData){
     Std_ReturnType ret = E_OK;
     /* Read the Interrupt status "Enabled/Disabled" */
     uint8 Global_inturrpt_st = INTCONbits.GIE;
     /* Update the Address Register */
     EEADRH = (uint8)((bAdd >>8) & 0x03);
     EEADR = (uint8)(bAdd & 0xFF) ;
     /* Update the Data Register */
     EEDATA = bData;
     /* Access to the Address Data EEPROM Memory */
     EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
     EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
     /* Allow Write Cycle to Flash/EEPROM memory */
     EECON1bits.WREN = ALLOW_WRITE_CYCLE_FLASH_EEPROM;
     /* Disable all the Global Interrupts */
     INTERRUPT_GlobalInterruptDisable();
     /* Write the Required Sequence " 0x55-0xAA " */
     EECON2 = 0x55;
     EECON2 = 0xAA;
     /* Intiates a Data EEPROM Write/Erase cycle */
     EECON1bits.WR = INTIATE_DATA_EEPROM_WRITE_ERASE;
     /* Wait for write to be completed */
     while(EECON1bits.WR);
     /* Inhabit write cycle to Flash program/EEPROM data memory */
     EECON1bits.WR = INHABIT_WRITE_CYCLE_FLASH_EEPROM;
     /* Restore the Interrupt status "Enabled/Disabled" */
     INTCONbits.GIE = Global_inturrpt_st;
     return(ret);
}
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData){
     Std_ReturnType ret = E_OK;
     
     if(NULL== bData){
         ret= E_NOK;
     }
     else{
        /* Update the Address Register */
         EEADRH = (uint8)((bAdd >>8) & 0x03);
         EEADR = (uint8)(bAdd & 0xFF) ;
         /* Access to the Address Data EEPROM Memory */
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
        EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
        /* Intiates a Data EEPROM Read cycle */
        EECON1bits.RD = INTIATE_DATA_EEPROM_READ;
        NOP();
        NOP();
        /* Return data */
        *bData = EEDATA;
     }
     return(ret);
}