/* 
 * File:   ecu_led.h
 * Author: LENOVO
 *
 * Created on 14 March 2024, 20:15
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/*section of INCLUDES */

#include"../../MCAL_layer/GPIO/hal_gpio.h"
#include"ecu_led_cfg.h"

/*section of MACRO DECLARATIONS */

/*section of MACRO FUNCTIONS DECLARATIONS */
typedef enum{
    LED_OFF,
    LED_ON        
}LED_STATUS_t;

typedef struct{
    uint8 port_name : 4;
    uint8 pin : 3;
    uint8 led_status : 1;
}led_t;

/*section of MACRO DECLARATIONS */

/*section of FUNCTIONS DECLARATIONS */

Std_ReturnType led_intialization(const led_t *LED);
Std_ReturnType led_turn_on(const led_t *LED);
Std_ReturnType led_turn_off(const led_t *LED);
Std_ReturnType led_toggle(const led_t *LED);

#endif	/* ECU_LED_H */

