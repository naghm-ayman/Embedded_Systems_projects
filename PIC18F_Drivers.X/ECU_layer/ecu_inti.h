/* 
 * File:   ecu_inti.h
 * Author: Naghm Ayman Omar
 *
 * Created on 10 May 2024, 19:14
 */

#ifndef ECU_INTI_H
#define	ECU_INTI_H

/*section of INCLUDES */

#include"LED/ecu_led.h"
#include"BUTTON/ecu_button.h"
#include"RELAY/ecu_relay.h"
#include"DC_MOTOR/ecu_dc_motor.h"
#include"7_Segment/ecu_seven_segment.h"
#include"KEYBAD/ecu_keybad.h"
#include"Chr_LCD/ecu_chr_lcd.h"

/*section of MACRO DECLARATIONS */
/*section of MACRO FUNCTIONS DECLARATIONS */

/*section of FUNCTIONS DECLARATIONS*/

void ecu_layer_intialize(void);

#endif	/* ECU_INTI_H */

