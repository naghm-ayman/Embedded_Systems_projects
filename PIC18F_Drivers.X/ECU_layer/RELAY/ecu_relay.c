/* 
 * File:   ecu_relay.c
 * Author: Naghm Ayman Omar
 *
 * Created on 01 May 2024, 16:12
 */

#include"ecu_relay.h"


Std_ReturnType relay_intialization(const relay_t *relay){
    Std_ReturnType ret = E_OK;
     
     if(NULL == relay){
         ret= E_NOK;
     }
     else{
         pin_config_t relay_obj={
           .port = relay->relay_port,
           .pin = relay->relay_pin,
           .direction = GPIO_Output_direction,
           .logic = relay->relay_status
         };
         ret = gpio_pin_intialize(&relay_obj);
     }
     return(ret);
}
Std_ReturnType relay_turn_on(const relay_t *relay){
    Std_ReturnType ret = E_OK;
     
     if(NULL == relay){
         ret= E_NOK;
     }
     else{
          pin_config_t relay_obj={
           .port = relay->relay_port,
           .pin = relay->relay_pin,
           .direction = GPIO_Output_direction,
           .logic = relay->relay_status
         };
          ret = gpio_pin_write_logic(&relay_obj,GPIO_HIGH);
     }
     return(ret);
}
Std_ReturnType relay_turn_off(const relay_t *relay){
    Std_ReturnType ret = E_OK;
     
     if(NULL == relay){
         ret= E_NOK;
     }
     else{
          pin_config_t relay_obj={
           .port = relay->relay_port,
           .pin = relay->relay_pin,
           .direction = GPIO_Output_direction,
           .logic = relay->relay_status
         };
          ret = gpio_pin_write_logic(&relay_obj,GPIO_LOW);
     }
     return(ret);
}