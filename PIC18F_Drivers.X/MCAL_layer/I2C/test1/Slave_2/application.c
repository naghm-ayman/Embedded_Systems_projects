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


volatile uint8 i2c_rec_2_counter;
void MSSP_I2C_Defult_InteruuptHandller(void){
       i2c_rec_2_counter++;
}
int main() {
    Std_ReturnType ret = E_NOK;
    intialization_fun();
  
//    i2c_obj.i2c_clock = 100000;
    i2c_obj.i2c_config.i2c_mode = I2C_MSSP_SLAVE_MODE;
    i2c_obj.i2c_config.i2c_slave_address = 0x62;
    i2c_obj.i2c_config.i2c_mode_cfg = I2C_SLAVE_MODE_7BIT_ADDRESS;
    i2c_obj.i2c_config.i2c_general_call = I2C_GENERAL_CALL_DISABLE;
    i2c_obj.i2c_config.i2c_slew_rate = SLEW_RATE_DISABLED;
    i2c_obj.i2c_config.i2c_SMBus_control = SMBus_INPUT_DISABLED;
    i2c_obj.I2C_InterruptHandler = MSSP_I2C_Defult_InteruuptHandller;
    i2c_obj.I2C_Report_Receive_Overflow = NULL;
    i2c_obj.I2C_Report_Write_Collision = NULL;
    
    ret = MSSP_I2C_Init(&i2c_obj);
    
    
 while(1) {
//     MSSP_I2C_Send_BYTE(SLAVE1, 'a');
//        __delay_ms(200);
//     MSSP_I2C_Send_BYTE(SLAVE2, 'b');
//        __delay_ms(200);
//     MSSP_I2C_Send_BYTE(SLAVE1, 'c');
//        __delay_ms(200);
//     MSSP_I2C_Send_BYTE(SLAVE2, 'd');
//        __delay_ms(200);
  }
     return(EXIT_SUCCESS);

 }
void intialization_fun(void){
    Std_ReturnType ret = E_NOK;
    ecu_layer_intialize();
}