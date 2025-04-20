/* 
 * File:   ecu_led.c
 * Author: LENOVO
 *
 * Created on 14 March 2024, 20:15
 */

#include"ecu_led.h"

Std_ReturnType led_intialization(const led_t *LED){
     Std_ReturnType ret = E_OK;
     
     if(NULL== LED){
         ret= E_NOK;
     }
     else{
         pin_config_t pin_obj ={
      .port = LED->port_name,
      .pin = LED->pin,
      .direction = GPIO_Output_direction,
      .logic = LED->led_status
     };
        ret= gpio_pin_intialize(&pin_obj);
         
     }
     return(ret);
}
Std_ReturnType led_turn_on(const led_t *LED){
     Std_ReturnType ret = E_OK;
       if(NULL== LED){
         ret= E_NOK;
     }
     else{
          pin_config_t pin_obj ={
      .port = LED->port_name,
      .pin = LED->pin,
      .direction = GPIO_Output_direction,
      .logic = LED->led_status
     };
             ret = gpio_pin_write_logic(&pin_obj,GPIO_HIGH);
         
     }
     return(ret);
}
Std_ReturnType led_turn_off(const led_t *LED){
     Std_ReturnType ret = E_OK;
       if(NULL== LED){
         ret= E_NOK;
     }
     else{
         pin_config_t pin_obj={
      .port = LED->port_name,
      .pin = LED->pin,
      .direction = GPIO_Output_direction,
      .logic = LED->led_status
     };
             ret = gpio_pin_write_logic(&pin_obj,GPIO_LOW);
         
     }
     return(ret);
}
Std_ReturnType led_toggle(const led_t *LED){
     Std_ReturnType ret = E_OK;
       if(NULL== LED){
         ret= E_NOK;
     }
     else{
                pin_config_t pin_obj ={
      .port = LED->port_name,
      .pin = LED->pin,
      .direction = GPIO_Output_direction,
      .logic = LED->led_status
     };
             ret = gpio_pin_toggle_logic(&pin_obj);
         
     }
     return(ret);
}