/* 
 * File:   ecu_inti.c
 * Author: Naghm Ayman Omar
 *
 * Created on 10 May 2024, 19:14
 */

#include"ecu_inti.h"


chr_lcd_4bit_t lcd_1 = {
    .LCD_rs.port = PortC_index,
    .LCD_rs.pin = GPIO_Pin0,
    .LCD_rs.direction = GPIO_Output_direction,
    .LCD_rs.logic = GPIO_LOW,
    .LCD_en.port = PortC_index,
    .LCD_en.pin = GPIO_Pin1,
    .LCD_en.direction = GPIO_Output_direction,
    .LCD_en.logic = GPIO_LOW,
    .LCD_data[0].port = PortC_index,
    .LCD_data[0].pin = GPIO_Pin2,
    .LCD_data[0].direction = GPIO_Output_direction,
    .LCD_data[0].logic = GPIO_LOW,
    .LCD_data[1].port = PortC_index,
    .LCD_data[1].pin = GPIO_Pin3,
    .LCD_data[1].direction = GPIO_Output_direction,
    .LCD_data[1].logic = GPIO_LOW,
    .LCD_data[2].port = PortC_index,
    .LCD_data[2].pin = GPIO_Pin4,
    .LCD_data[2].direction = GPIO_Output_direction,
    .LCD_data[2].logic = GPIO_LOW,
    .LCD_data[3].port = PortC_index,
    .LCD_data[3].pin = GPIO_Pin5,
    .LCD_data[3].direction = GPIO_Output_direction,
    .LCD_data[3].logic = GPIO_LOW
};

chr_lcd_8bit_t lcd_2 = {
    .LCD_rs.port = PortC_index,
    .LCD_rs.pin = GPIO_Pin6,
    .LCD_rs.direction = GPIO_Output_direction,
    .LCD_rs.logic = GPIO_LOW,
    .LCD_en.port = PortC_index,
    .LCD_en.pin = GPIO_Pin7,
    .LCD_en.direction = GPIO_Output_direction,
    .LCD_en.logic = GPIO_LOW,
    .LCD_data[0].port = PortD_index,
    .LCD_data[0].pin = GPIO_Pin0,
    .LCD_data[0].direction = GPIO_Output_direction,
    .LCD_data[0].logic = GPIO_LOW,
    .LCD_data[1].port = PortD_index,
    .LCD_data[1].pin = GPIO_Pin1,
    .LCD_data[1].direction = GPIO_Output_direction,
    .LCD_data[1].logic = GPIO_LOW,
    .LCD_data[2].port = PortD_index,
    .LCD_data[2].pin = GPIO_Pin2,
    .LCD_data[2].direction = GPIO_Output_direction,
    .LCD_data[2].logic = GPIO_LOW,
    .LCD_data[3].port = PortD_index,
    .LCD_data[3].pin = GPIO_Pin3,
    .LCD_data[3].direction = GPIO_Output_direction,
    .LCD_data[3].logic = GPIO_LOW,
    .LCD_data[4].port = PortD_index,
    .LCD_data[4].pin = GPIO_Pin4,
    .LCD_data[4].direction = GPIO_Output_direction,
    .LCD_data[4].logic = GPIO_LOW,
    .LCD_data[5].port = PortD_index,
    .LCD_data[5].pin = GPIO_Pin5,
    .LCD_data[5].direction = GPIO_Output_direction,
    .LCD_data[5].logic = GPIO_LOW,
    .LCD_data[6].port = PortD_index,
    .LCD_data[6].pin = GPIO_Pin6,
    .LCD_data[6].direction = GPIO_Output_direction,
    .LCD_data[6].logic = GPIO_LOW,
    .LCD_data[7].port = PortD_index,
    .LCD_data[7].pin = GPIO_Pin7,
    .LCD_data[7].direction = GPIO_Output_direction,
    .LCD_data[7].logic = GPIO_LOW
};



void ecu_layer_intialize(void){
    Std_ReturnType ret = E_NOK;
    ret = lcd_4bit_intialize(&lcd_1);
     ret = lcd_8bit_intialize(&lcd_2);
}
