/* 
 * File:   ecu_relay.h
 * Author: Naghm Ayman Omar
 *
 * Created on 01 May 2024, 16:12
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H


/*section of INCLUDES */
#include"../../MCAL_layer/GPIO/hal_gpio.h"
#include"ecu_relay_cfg.h"

/*section of MACRO DECLARATIONS */
#define Relay_OFF_status    0x00U
#define Relay_ON_status     0x01U
/*section of MACRO FUNCTIONS DECLARATIONS */

/*section of DATA TYPES*/

typedef struct{
    uint8 relay_port : 4;
    uint8 relay_pin  : 3;
    uint8 relay_status : 1;
}relay_t;

/*section of FUNCTIONS DECLARATIONS*/

Std_ReturnType relay_intialization(const relay_t *relay);
Std_ReturnType relay_turn_on(const relay_t *relay);
Std_ReturnType relay_turn_off(const relay_t *relay);



#endif	/* ECU_RELAY_H */

