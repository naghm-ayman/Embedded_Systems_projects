/* 
 * File:   ecu_keybad.h
 * Author: Naghm Ayman Omar
 *
 * Created on 09 May 2024, 18:50
 */

#ifndef ECU_KEYBAD_H
#define	ECU_KEYBAD_H


/*section of INCLUDES */
#include"../../MCAL_layer/GPIO/hal_gpio.h"
#include"ecu_keybad_cfg.h"

/*section of MACRO DECLARATIONS */
#define ECU_KEYBAD_ROW      4
#define ECU_KEYBAD_COLUMN   4

/*section of MACRO FUNCTIONS DECLARATIONS */

/*section of DATA TYPES DECLARATIONS*/
typedef struct{
    pin_config_t keybad_row_pin[ECU_KEYBAD_ROW];
    pin_config_t keybad_column_pin[ECU_KEYBAD_COLUMN];
}keybad_t;
/*section of FUNCTIONS DECLARATIONS*/
Std_ReturnType keybad_intialization(const keybad_t *keybad_obj);
Std_ReturnType keybad_get_value(const keybad_t *keybad_obj, uint8 *value);


#endif	/* ECU_KEYBAD_H */

