/* 
 * File:   application.c
 * Author: NAGHM.A.O
 *
 * Created on 14 March 2024, 20:02
 */

#include "application.h"

Std_ReturnType ret = E_NOK;

mssp_i2c_t i2c_obj;
uint8 slave_ack;
uint8 counter;

#define SLAVE1 0x60
#define SLAVE2 0x62

void MSSP_I2C_Send_BYTE(uint8 slave_add, uint8 data){
        ret = MSSP_I2C_Master_Send_Start(&i2c_obj);
        ret = MSSP_I2C_Master_Write_Blocking(&i2c_obj, slave_add, &slave_ack);
        ret = MSSP_I2C_Master_Write_Blocking(&i2c_obj, data, &slave_ack);
        ret = MSSP_I2C_Master_Send_Stop(&i2c_obj);
}
int main() {
    Std_ReturnType ret = E_NOK;
    intialization_fun();
  
    i2c_obj.i2c_clock = 100000;
    i2c_obj.i2c_config.i2c_mode = I2C_MSSP_MASTER_MODE;
    i2c_obj.i2c_config.i2c_mode_cfg = I2C_MASTER_MODE_DEFINED_CLOCK;
    i2c_obj.i2c_config.i2c_slew_rate = SLEW_RATE_DISABLED;
    i2c_obj.i2c_config.i2c_SMBus_control = SMBus_INPUT_DISABLED;
    //i2c_obj.I2C_InterruptHandler = NULL;
   // i2c_obj.I2C_Report_Receive_Overflow = NULL;
   // i2c_obj.I2C_Report_Write_Collision = NULL;
    
    ret = MSSP_I2C_Init(&i2c_obj);
    
    
 while(1) {
     MSSP_I2C_Send_BYTE(SLAVE1, 'a');
        __delay_ms(200);
     MSSP_I2C_Send_BYTE(SLAVE2, 'b');
        __delay_ms(200);
     MSSP_I2C_Send_BYTE(SLAVE1, 'c');
        __delay_ms(200);
     MSSP_I2C_Send_BYTE(SLAVE2, 'd');
        __delay_ms(200);
     counter++;
  }
     return(EXIT_SUCCESS);

 }
void intialization_fun(void){
    Std_ReturnType ret = E_NOK;
    ecu_layer_intialize();
}