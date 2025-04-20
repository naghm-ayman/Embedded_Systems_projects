/* 
 * File:   ecu_dc_motor.c
 * Author: Naghm Ayman Omar
 *
 * Created on 02 May 2024, 16:07
 */

#include"ecu_dc_motor.h"


Std_ReturnType dc_motor_intialization(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
     
     if(NULL == _dc_motor){
         ret= E_NOK;
     }
     else{
       
          ret = gpio_pin_intialize(&(_dc_motor->dc_motor[DC_motor_Pin1]));
          ret = gpio_pin_intialize(&(_dc_motor->dc_motor[DC_motor_Pin2]));
        
     }
     return(ret);
}
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor){
     Std_ReturnType ret = E_OK;
     
     if(NULL == _dc_motor){
         ret= E_NOK;
     }
     else{
         ret = gpio_pin_write_logic(&(_dc_motor->dc_motor[DC_motor_Pin1]),GPIO_HIGH);
         ret = gpio_pin_write_logic(&(_dc_motor->dc_motor[DC_motor_Pin2]),GPIO_LOW);

     }
     return(ret);
}
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor){
     Std_ReturnType ret = E_OK;
     
     if(NULL == _dc_motor){
         ret= E_NOK;
     }
     else{
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor[DC_motor_Pin1]),GPIO_LOW);
         ret = gpio_pin_write_logic(&(_dc_motor->dc_motor[DC_motor_Pin2]),GPIO_HIGH);
     }
     return(ret);
}
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor){
     Std_ReturnType ret = E_OK;
     
     if(NULL == _dc_motor){
         ret= E_NOK;
     }
     else{
         ret = gpio_pin_write_logic(&(_dc_motor->dc_motor[DC_motor_Pin1]),GPIO_LOW);
         ret = gpio_pin_write_logic(&(_dc_motor->dc_motor[DC_motor_Pin2]),GPIO_LOW);
     }
     return(ret);
}