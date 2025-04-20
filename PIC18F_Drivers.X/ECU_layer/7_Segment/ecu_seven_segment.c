/* 
 * File:   ecu_seven_segment.c
 * Author: Naghm Ayman Omar
 *
 * Created on 06 May 2024, 16:06
 */

#include"ecu_seven_segment.h"

Std_ReturnType seven_segment_intialize(const segment_t *seg){
    Std_ReturnType ret = E_OK;
     
     if(NULL== seg){
         ret= E_NOK;
     }
     else{
        ret = gpio_pin_intialize(&(seg->segment_pin[Segment_PIN0]));
        ret = gpio_pin_intialize(&(seg->segment_pin[Segment_PIN1]));
        ret = gpio_pin_intialize(&(seg->segment_pin[Segment_PIN2]));
        ret = gpio_pin_intialize(&(seg->segment_pin[Segment_PIN3]));
     }
     return(ret);
}
Std_ReturnType seven_segment_write_logic(const segment_t *seg,uint8 number){
    Std_ReturnType ret = E_OK;
     
     if((NULL== seg) &&(number > 9)){
         ret= E_NOK;
     }
     else{
         ret = gpio_pin_write_logic(&(seg->segment_pin[Segment_PIN0]), (number & 0x01));
         ret = gpio_pin_write_logic(&(seg->segment_pin[Segment_PIN1]), ((number>>1) & 0x01));
         ret = gpio_pin_write_logic(&(seg->segment_pin[Segment_PIN2]), ((number>>2) & 0x01));
         ret = gpio_pin_write_logic(&(seg->segment_pin[Segment_PIN3]), ((number>>3) & 0x01));
     }
     return(ret);
}