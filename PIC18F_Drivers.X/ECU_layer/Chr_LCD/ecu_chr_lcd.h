/* 
 * File:   ecu_chr_lcd.h
 * Author: Naghm Ayman Omar
 *
 * Created on 02 July 2024, 16:51
 */

#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H

/*section of INCLUDES */
#include"../../MCAL_layer/GPIO/hal_gpio.h"
#include"ecu_chr_lcd_cfg.h"

/*section of MACRO DECLARATIONS */
#define LCD_CLEAR                    0x01
#define LCD_RETURN_HOME              0x02
#define LCD_ENTRY_MODE               0x06
#define LCD_CURSOR_OFF_DISPLAY_ON    0x0C
#define LCD_CURSOR_OFF_DISPLAY_OFF   0x08
#define LCD_CURSOR_ON_BLINK_ON       0x0F
#define LCD_CURSOR_OFF_BLINK_OFF     0x0E
#define LCD_DISPLAY_SHIFT_RIGHT      0x1C
#define LCD_DISPLAY_SHIFT_LEFT       0x18
#define LCD_8BIT_MODE_2_LINE         0x38
#define LCD_4BIT_MODE_2_LINE         0x28
#define LCD_CGRAM_START_ADD          0x40
#define LCD_DDRAM_START_ADD          0x80

#define ROW1    1
#define ROW2    2
#define ROW3    3
#define ROW4    4
/*section of MACRO FUNCTIONS DECLARATIONS */


/*section of Data types DECLARATIONS*/
typedef struct{
    pin_config_t LCD_rs;
    pin_config_t LCD_en;
    pin_config_t LCD_data[4];
}chr_lcd_4bit_t;

typedef struct{
    pin_config_t LCD_rs;
    pin_config_t LCD_en;
    pin_config_t LCD_data[8];
}chr_lcd_8bit_t;

/*section of FUNCTIONS DECLARATIONS*/
Std_ReturnType lcd_4bit_intialize(const chr_lcd_4bit_t *lcd);
Std_ReturnType lcd_4bit_send_comand(const chr_lcd_4bit_t *lcd, uint8 command);
Std_ReturnType lcd_4bit_send_data(const chr_lcd_4bit_t *lcd, uint8 data);
Std_ReturnType lcd_4bit_send_data_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data);
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd, uint8 *str);
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str);
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, const uint8 _char[], uint8 mem_pos);

Std_ReturnType lcd_8bit_intialize(const chr_lcd_8bit_t *lcd);
Std_ReturnType lcd_8bit_send_comand(const chr_lcd_8bit_t *lcd, uint8 command);
Std_ReturnType lcd_8bit_send_data(const chr_lcd_8bit_t *lcd, uint8 data);
Std_ReturnType lcd_8bit_send_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data);
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *str);
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str);
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, const uint8 _char[], uint8 mem_pos);

Std_ReturnType conv_byte_to_string(uint8 value, uint8 *str);
Std_ReturnType conv_short_to_string(uint16 value, uint8 *str);
Std_ReturnType conv_int_to_string(uint32 value, uint8 *str);
#endif	/* ECU_CHR_LCD_H */

