/* 
 * File:   application.h
 * Author: LENOVO
 *
 * Created on 14 March 2024, 20:17
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/*section of INCLUDES */
#include "ECU_layer/ecu_inti.h"
#include"MCAL_layer/Interrupt/mcal_external_interrupt.h"
#include"MCAL_layer/EEPROM/hal_eeprom.h"
#include"MCAL_layer/ADC/hal_adc.h"
#include"MCAL_layer/TIMER/hal_timer0.h"
#include"MCAL_layer/TIMER1/hal_timer1.h"
#include"MCAL_layer/TIMER2/hal_timer2.h"
#include"MCAL_layer/TIMER3/hal_timer3.h"
#include"MCAL_layer/CCP1/hal_ccp1.h"
#include"MCAL_layer/USART/hal_usart.h"
#include"MCAL_layer/I2C/hal_i2c.h"


/*section of MACRO DECLARATIONS */
extern keybad_t keybad1;
extern led_t led1;
extern chr_lcd_8bit_t lcd_2;
extern chr_lcd_4bit_t lcd_1;
/*section of MACRO FUNCTIONS DECLARATIONS */

/*section of FUNCTIONS DECLARATIONS*/
void intialization_fun(void);
void Int0_APP_ISR(void);
#endif	/* APPLICATION_H */

