/* 
 * File:   ecu_dc_motor.h
 * Author: Naghm Ayman Omar
 *
 * Created on 02 May 2024, 16:07
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/*section of INCLUDES */
#include"../../MCAL_layer/GPIO/hal_gpio.h"
#include"ecu_dc_motor_cfg.h"

/*section of MACRO DECLARATIONS */
#define DC_motor_OFF_status    0x00U
#define DC_motor_ON_status     0x01U

#define DC_motor_Pin1     0x00U
#define DC_motor_Pin2     0x01U
/*section of MACRO FUNCTIONS DECLARATIONS */


/*section of Data types DECLARATIONS*/

typedef struct{
   pin_config_t dc_motor[2];
}dc_motor_t;

/*section of FUNCTIONS DECLARATIONS*/
Std_ReturnType dc_motor_intialization(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor);


#endif	/* ECU_DC_MOTOR_H */

