/* 
 * File:   ecu_button.c
 * Author: Naghm Ayman Omar
 *
 * Created on 26 April 2024, 17:54
 */

#include"ecu_button.h"

Std_ReturnType button_intialization(const button_t *btn){
     Std_ReturnType ret = E_OK;
     
     if(NULL== btn){
         ret= E_NOK;
     }
     else{
         ret=gpio_pin_direction_intialize(&(btn->button_config));
     }
     return(ret);
}
Std_ReturnType button_read(const button_t *btn, button_state_t *btn_st){
     Std_ReturnType ret = E_OK;
     logic_t pin_logic_st= GPIO_LOW;
     if((NULL== btn)||(NULL==btn_st)){
         ret= E_NOK;
     }
     else{
         ret = gpio_pin_read_logic(&(btn->button_config),&pin_logic_st);
         if(Button_Active_High==(btn->button_connection)){
             if(GPIO_HIGH== pin_logic_st){
                 *btn_st = Button_pressed;
             }
             else{
                  *btn_st = Button_Released;
             }
         }
         else if(Button_Active_Low==(btn->button_connection)){
             if(GPIO_HIGH== pin_logic_st){
                 *btn_st = Button_Released;
             }
             else{
                  *btn_st = Button_pressed;
             }
         }
         else{
             /*NOTHING*/
         }
        ret = E_OK; 
     }
     return(ret);
}