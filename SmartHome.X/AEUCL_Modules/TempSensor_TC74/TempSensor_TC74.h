/* 
 * File:   TempSensor_TC74.h
 * Author: Naghm Ayman Omar
 *
 * Created on 18 September 2024, 18:45
 */

#ifndef TEMPSENSOR_TC74_H
#define	TEMPSENSOR_TC74_H

/*-------------------- INCLUDES Sections ----------------------*/
#include"../../mcc_generated_files/mcc.h"
#include"../../mcc_generated_files/examples/i2c_master_example.h"


/*-------------------- SOFTWARE INTERFACES ----------------------*/
uint8_t TempSensor_TC74_Read_Temp(i2c_address_t TC74_Address);
#endif	/* TEMPSENSOR_TC74_H */

