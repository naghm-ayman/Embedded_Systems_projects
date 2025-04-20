/* 
 * File:   ecu_keybad.c
 * Author: Naghm Ayman Omar
 *
 * Created on 09 May 2024, 18:50
 */
#include"ecu_keybad.h"


static const uint8 keybad_val[ECU_KEYBAD_ROW][ECU_KEYBAD_COLUMN]={
                                   {'7','8','9','/'},
                                   {'4','5','6','*'},
                                   {'1','2','2','-'},
                                   {'#','0','=','+'},
};

Std_ReturnType keybad_intialization(const keybad_t *keybad_obj){
    Std_ReturnType ret = E_OK;
    uint8 row_counter = ZERO_INIT;
    uint8 coulmn_counter = ZERO_INIT;
     if(NULL == keybad_obj){
         ret= E_NOK;
     }
     else{
         for(row_counter = ZERO_INIT; row_counter < ECU_KEYBAD_ROW; row_counter++){
             ret = gpio_pin_intialize(&(keybad_obj->keybad_row_pin[row_counter]));
         }
         for(coulmn_counter = ZERO_INIT; coulmn_counter < ECU_KEYBAD_COLUMN; coulmn_counter++){
             ret = gpio_pin_direction_intialize(&(keybad_obj->keybad_column_pin[coulmn_counter]));
         }
     }
     return(ret);
}
Std_ReturnType keybad_get_value(const keybad_t *keybad_obj, uint8 *value){
    Std_ReturnType ret = E_OK;
    
     uint8 row_counter = ZERO_INIT;
     uint8 coulmn_counter = ZERO_INIT;
     uint8 counter = ZERO_INIT;
     uint8 coulmn_logic = ZERO_INIT;
     
     if((NULL == keybad_obj)||(NULL == value)){
         ret= E_NOK;
     }
     else{
         for(row_counter = ZERO_INIT; row_counter < ECU_KEYBAD_ROW; row_counter++){
             for(counter = ZERO_INIT; counter < ECU_KEYBAD_ROW; counter++){
                 ret = gpio_pin_write_logic(&(keybad_obj->keybad_row_pin[counter]), GPIO_LOW);
             }
                 ret = gpio_pin_write_logic(&(keybad_obj->keybad_row_pin[row_counter]), GPIO_HIGH);
                 for(coulmn_counter = ZERO_INIT; coulmn_counter < ECU_KEYBAD_COLUMN; coulmn_counter++){
             ret = gpio_pin_read_logic(&(keybad_obj->keybad_column_pin[coulmn_counter]),&coulmn_logic);
             if(GPIO_HIGH == coulmn_logic){
                 *value = keybad_val[row_counter][coulmn_counter];
             }
         }

         }
     }
     return(ret);
}
