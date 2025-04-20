/* 
 * File:   ecu_chr_lcd.h
 * Author: Naghm Ayman Omar
 *
 * Created on 02 July 2024, 16:51
 */

#include"ecu_chr_lcd.h"

static Std_ReturnType lcd_send_4_bits(const chr_lcd_4bit_t *lcd, uint8 _data_command);
static Std_ReturnType lcd_send_4_bits_enable_signal(const chr_lcd_4bit_t *lcd);
static Std_ReturnType lcd_4_bits_set_cusor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column);

static Std_ReturnType lcd_send_8_bits_enable_signal(const chr_lcd_8bit_t *lcd);
static Std_ReturnType lcd_8_bits_set_cusor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column);


Std_ReturnType lcd_4bit_intialize(const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret= E_OK;
    uint8 l_data_pin_counter = ZERO_INIT;
     if(NULL == lcd){
         ret= E_NOK;
     }
     else{
         ret = gpio_pin_intialize(&(lcd->LCD_rs));
         ret = gpio_pin_intialize(&(lcd->LCD_en));
         for(l_data_pin_counter = ZERO_INIT; l_data_pin_counter < 4; l_data_pin_counter++){
             ret = gpio_pin_intialize(&(lcd->LCD_data[l_data_pin_counter]));
         }
           __delay_ms(20);
         ret = lcd_4bit_send_comand(lcd, LCD_8BIT_MODE_2_LINE);
         __delay_ms(5);
         ret = lcd_4bit_send_comand(lcd, LCD_8BIT_MODE_2_LINE);
         __delay_us(150);
         ret = lcd_4bit_send_comand(lcd, LCD_8BIT_MODE_2_LINE);
         ret = lcd_4bit_send_comand(lcd, LCD_CLEAR);
         ret = lcd_4bit_send_comand(lcd, LCD_RETURN_HOME);
         ret = lcd_4bit_send_comand(lcd, LCD_ENTRY_MODE);
         ret = lcd_4bit_send_comand(lcd, LCD_CURSOR_OFF_DISPLAY_ON);
         ret = lcd_4bit_send_comand(lcd, LCD_4BIT_MODE_2_LINE);
         ret = lcd_4bit_send_comand(lcd, 0x80);
     }
     return(ret);
    
}
Std_ReturnType lcd_4bit_send_comand(const chr_lcd_4bit_t *lcd, uint8 command){
     Std_ReturnType ret= E_OK;
     if(NULL == lcd){
         ret= E_NOK;
     }
     else{
           ret = gpio_pin_write_logic(&(lcd->LCD_rs), GPIO_LOW);
           ret = lcd_send_4_bits(lcd, (command >> 4));
           ret = lcd_send_4_bits_enable_signal(lcd);
           ret = lcd_send_4_bits(lcd, command );      
           ret = lcd_send_4_bits_enable_signal(lcd);

     }
     return(ret);
    
}

Std_ReturnType lcd_4bit_send_data(const chr_lcd_4bit_t *lcd, uint8 data){
     Std_ReturnType ret= E_OK;
     if(NULL == lcd){
         ret= E_NOK;
     }
     else{
           ret = gpio_pin_write_logic(&(lcd->LCD_rs), GPIO_HIGH);
           ret = lcd_send_4_bits(lcd, (data >> 4));
           ret = lcd_send_4_bits_enable_signal(lcd);
           ret = lcd_send_4_bits(lcd, data );      
           ret = lcd_send_4_bits_enable_signal(lcd);

     }
     return(ret);
    
}
Std_ReturnType lcd_4bit_send_data_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data){
     Std_ReturnType ret= E_OK;
     if(NULL == lcd){
         ret= E_NOK;
     }
     else{
         ret = lcd_4_bits_set_cusor(lcd, row, column);
         ret = lcd_4bit_send_data(lcd, data);
     }
     return(ret);
    
}
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd, uint8 *str){
     Std_ReturnType ret= E_OK;
     if((NULL == lcd)||(NULL == str)){
         ret= E_NOK;
     }
     else{
         while(*str){
             ret = lcd_4bit_send_data(lcd, *str++);
         }
     }
     return(ret);
}
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str){
       Std_ReturnType ret= E_OK;
     if((NULL == lcd)||(NULL == str)){
         ret= E_NOK;
     }
     else{
         lcd_4_bits_set_cusor(lcd, row, column);
         while(*str){
             ret = lcd_4bit_send_data(lcd, *str++);
         }
     }
     return(ret);
}
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, const uint8 _char[], uint8 mem_pos){
    Std_ReturnType ret= E_OK;
    uint8 l_counter = ZERO_INIT;
     if(NULL == lcd){
         ret= E_NOK;
     }
     else{
         ret = lcd_4bit_send_comand(lcd,(LCD_CGRAM_START_ADD + (mem_pos*8)));
         for(l_counter = ZERO_INIT; l_counter <= 7; l_counter++){
             ret = lcd_4bit_send_data(lcd,_char[l_counter]);
         }
         ret = lcd_4bit_send_data_pos(lcd, row, column, mem_pos);
     }
     return(ret);
}

Std_ReturnType lcd_8bit_intialize(const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret= E_OK;
    uint8 l_data_pin_counter = ZERO_INIT;
     if(NULL == lcd){
         ret= E_NOK;
     }
     else{
         ret = gpio_pin_intialize(&(lcd->LCD_rs));
         ret = gpio_pin_intialize(&(lcd->LCD_en));
         for(l_data_pin_counter = ZERO_INIT; l_data_pin_counter < 8; l_data_pin_counter++){
             ret = gpio_pin_intialize(&(lcd->LCD_data[l_data_pin_counter]));
         }
         __delay_ms(20);
         ret = lcd_8bit_send_comand(lcd, LCD_8BIT_MODE_2_LINE);
         __delay_ms(5);
         ret = lcd_8bit_send_comand(lcd, LCD_8BIT_MODE_2_LINE);
         __delay_us(150);
         ret = lcd_8bit_send_comand(lcd, LCD_8BIT_MODE_2_LINE);
         ret = lcd_8bit_send_comand(lcd, LCD_CLEAR);
         ret = lcd_8bit_send_comand(lcd, LCD_RETURN_HOME);
         ret = lcd_8bit_send_comand(lcd, LCD_ENTRY_MODE);
         ret = lcd_8bit_send_comand(lcd, LCD_CURSOR_OFF_DISPLAY_ON);
         ret = lcd_8bit_send_comand(lcd, LCD_8BIT_MODE_2_LINE);
         ret = lcd_8bit_send_comand(lcd, 0x80);
     }
     return(ret);
}
Std_ReturnType lcd_8bit_send_comand(const chr_lcd_8bit_t *lcd, uint8 command){
    Std_ReturnType ret= E_OK;
    uint8 l_pin_counter = ZERO_INIT;
     if(NULL == lcd){
         ret= E_NOK;
     }
     else{
          ret = gpio_pin_write_logic(&(lcd->LCD_rs), GPIO_LOW);
          for(l_pin_counter = ZERO_INIT; l_pin_counter < 8; ++l_pin_counter){
            ret = gpio_pin_write_logic(&(lcd->LCD_data[l_pin_counter]), (command >> l_pin_counter) & (uint8)0x01);
          }
          ret = lcd_send_8_bits_enable_signal(lcd);
     }
     return(ret);
}
Std_ReturnType lcd_8bit_send_data(const chr_lcd_8bit_t *lcd, uint8 data){
    Std_ReturnType ret= E_OK;
    uint8 l_pin_counter = ZERO_INIT;
     if(NULL == lcd){
         ret= E_NOK;
     }
     else{
          ret = gpio_pin_write_logic(&(lcd->LCD_rs), GPIO_HIGH);
           for(l_pin_counter = ZERO_INIT; l_pin_counter < 8; ++l_pin_counter){
            ret = gpio_pin_write_logic(&(lcd->LCD_data[l_pin_counter]), (data >> l_pin_counter) & (uint8)0x01);
          }
          ret = lcd_send_8_bits_enable_signal(lcd);
     }
     return(ret);
}
Std_ReturnType lcd_8bit_send_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data){
    Std_ReturnType ret= E_OK;
     if(NULL == lcd){
         ret= E_NOK;
     }
     else{
         ret = lcd_8_bits_set_cusor(lcd, row, column);
         ret = lcd_8bit_send_data(lcd, data);
     }
     return(ret);
}
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *str){
       Std_ReturnType ret= E_OK;
     if((NULL == lcd)||(NULL == str)){
         ret= E_NOK;
     }
     else{
         while(*str){
             ret = lcd_8bit_send_data(lcd, *str++);
         }
     }
     return(ret);
}
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str){
       Std_ReturnType ret= E_OK;
     if((NULL == lcd)||(NULL == str)){
         ret= E_NOK;
     }
     else{
         ret = lcd_8_bits_set_cusor(lcd, row, column);
          while(*str){
             ret = lcd_8bit_send_data(lcd, *str++);
         }
         
     }
     return(ret);
}
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, const uint8 _char[], uint8 mem_pos){
    Std_ReturnType ret= E_OK;
    uint8 l_counter = ZERO_INIT;
     if(NULL == lcd){
         ret= E_NOK;
     }
     else{
         ret = lcd_8bit_send_comand(lcd,(LCD_CGRAM_START_ADD + (mem_pos*8)));
         for(l_counter = ZERO_INIT; l_counter <= 7; l_counter++){
             ret = lcd_8bit_send_data(lcd,_char[l_counter]);
         }
         ret = lcd_8bit_send_data_pos(lcd, row, column, mem_pos);
         
     }
     return(ret);
}

Std_ReturnType conv_byte_to_string(uint8 value, uint8 *str){
    Std_ReturnType ret= E_OK;
     if(NULL == str){
         ret= E_NOK;
     }
     else{
         memset(str,'\0',4);
         sprintf(str,"%i",value);
     }
     return(ret);
}
Std_ReturnType conv_short_to_string(uint16 value, uint8 *str){
    Std_ReturnType ret= E_OK;
    uint8 Temp_counter[6] = {0} ;
    uint8 data_counter = 0;
     if(NULL == str){
         ret= E_NOK;
     }
     else{
           memset(str,' ',5);
           str[5] = '\0';
          sprintf((char*)Temp_counter,"%i",value);
          while(Temp_counter[data_counter] != '\0'){
              str[data_counter] = Temp_counter[data_counter];
              data_counter++;
          }
     }
     return(ret);
}
Std_ReturnType conv_int_to_string(uint32 value, uint8 *str){
    Std_ReturnType ret= E_OK;
     if(NULL == str){
         ret= E_NOK;
     }
     else{
           memset(str,'\0',11);
          sprintf(str,"%i",value);
     }
     return(ret);
}

static Std_ReturnType lcd_send_4_bits(const chr_lcd_4bit_t *lcd, uint8 _data_command){
    Std_ReturnType ret = E_OK;
    
    ret = gpio_pin_write_logic(&(lcd->LCD_data[0]), (_data_command >> 0) & (uint8)0x01);
    ret = gpio_pin_write_logic(&(lcd->LCD_data[1]), (_data_command >> 1) & (uint8)0x01);
    ret = gpio_pin_write_logic(&(lcd->LCD_data[2]), (_data_command >> 2) & (uint8)0x01);
    ret = gpio_pin_write_logic(&(lcd->LCD_data[3]), (_data_command >> 3) & (uint8)0x01);
    
    return(ret);
}

static Std_ReturnType lcd_send_4_bits_enable_signal(const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret = E_OK;
    
    ret = gpio_pin_write_logic(&(lcd->LCD_en), GPIO_HIGH);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(lcd->LCD_en), GPIO_LOW);
    return(ret);
}
static Std_ReturnType lcd_4_bits_set_cusor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column){
    Std_ReturnType ret = E_OK;
    column--;
    switch(row){
        case ROW1 : ret = lcd_4bit_send_comand(lcd, (0x80 + column));
        break;
        case ROW2 : ret = lcd_4bit_send_comand(lcd, (0xc0 + column));
        break;
        case ROW3 : ret = lcd_4bit_send_comand(lcd, (0x94 + column));
        break;
        case ROW4 : ret = lcd_4bit_send_comand(lcd, (0xd4 + column));
        break;
        default : /*nothing*/;
    }
 
    return(ret);
}
static Std_ReturnType lcd_send_8_bits_enable_signal(const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret = E_OK;
    
    ret = gpio_pin_write_logic(&(lcd->LCD_en), GPIO_HIGH);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(lcd->LCD_en), GPIO_LOW);
    return(ret);
}
static Std_ReturnType lcd_8_bits_set_cusor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column){
    Std_ReturnType ret = E_OK;
    column--;
    switch(row){
        case ROW1 : ret = lcd_8bit_send_comand(lcd, (0x80 + column));
        break;
        case ROW2 : ret = lcd_8bit_send_comand(lcd, (0xc0 + column));
        break;
        case ROW3 : ret = lcd_8bit_send_comand(lcd, (0x94 + column));
        break;
        case ROW4 : ret = lcd_8bit_send_comand(lcd, (0xd4 + column));
        break;
        default : /*nothing*/;
    }
 
    return(ret);
}