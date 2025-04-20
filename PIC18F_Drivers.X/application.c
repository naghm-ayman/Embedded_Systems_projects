/* 
 * File:   application.c
 * Author: NAGHM.A.O
 *
 * Created on 14 March 2024, 20:02
 */

#include "application.h"

Std_ReturnType ret = E_NOK;

volatile uint8 green_counter = ZERO_INIT;
void default_interrupt_handler(void){
    green_counter++;
    led_turn_on(&led1);
}

timer0_t timer_obj = {
    .TIMER0_InterruptHandler = default_interrupt_handler,
    .timer0_mode = TIMER1_TIMER_MODE,
    .timer0_register_size = TIMER1_RW_REG_16BITS_MODE,
    .prescaler_enable = TIMER0_PRESCALER_ENABLE_CFG,
    .prescaler_value = TIMER0_PRESCALER_DIV_BY_256,
    .timer0_preload_value = 18661,
};
led_t led1 ={
  .port_name = PortD_index,
  .pin = GPIO_Pin0,
  .led_status = GPIO_LOW
}; 
int main() {
    intialization_fun();
    ret = TIMER0_Init(&timer_obj);
    ret = led_intialization(&led1);
    
 while(1) {
//     if (green_counter){
//         led_turn_on(&led1);
//         green_counter = ZERO_INIT;
//     }
    
  }
     return(EXIT_SUCCESS);

 }
void intialization_fun(void){
    Std_ReturnType ret = E_NOK;
    ecu_layer_intialize();
}