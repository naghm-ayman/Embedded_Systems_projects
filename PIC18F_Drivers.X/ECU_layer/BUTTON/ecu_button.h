/* 
 * File:   ecu_button.h
 * Author: Naghm Ayman Omar
 *
 * Created on 26 April 2024, 17:54
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/*section of INCLUDES */
#include"../../MCAL_layer/GPIO/hal_gpio.h"
#include"ecu_button_cfg.h"

/*section of MACRO DECLARATIONS */

/*section of MACRO FUNCTIONS DECLARATIONS */

/*section of Data types DECLARATIONS*/

typedef enum{
    Button_pressed,
    Button_Released
}button_state_t;

typedef enum{
    Button_Active_High,
    Button_Active_Low
}button_active_state;

typedef struct{
    pin_config_t button_config;
    button_state_t button_state;
    button_active_state button_connection;
}button_t;



/*section of FUNCTIONS DECLARATIONS*/
Std_ReturnType button_intialization(const button_t *btn);
Std_ReturnType button_read(const button_t *btn, button_state_t *btn_st);

#endif	/* ECU_BUTTON_H */

