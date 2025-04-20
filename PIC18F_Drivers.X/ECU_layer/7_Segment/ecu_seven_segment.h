/* 
 * File:   ecu_seven_segment.h
 * Author: Naghm Ayman Omar
 *
 * Created on 06 May 2024, 16:06
 */

#ifndef ECU_SEVEN_SEGMENT_H
#define	ECU_SEVEN_SEGMENT_H

/*section of INCLUDES */
#include"../../MCAL_layer/GPIO/hal_gpio.h"
#include"ecu_seven_segment_cfg.h"

/*section of MACRO DECLARATIONS */
#define Segment_PIN0    0
#define Segment_PIN1    1
#define Segment_PIN2    2
#define Segment_PIN3    3

/*section of MACRO FUNCTIONS DECLARATIONS */

/*section of DATA TYPES DECLARATIONS*/
typedef enum{
    segment_common_anode,
    segment_common_cathode        
}segment_type_t;

typedef struct{
    pin_config_t segment_pin[4];
    segment_type_t segment_type;
}segment_t;

/*section of FUNCTIONS DECLARATIONS*/
Std_ReturnType seven_segment_intialize(const segment_t *seg);
Std_ReturnType seven_segment_write_logic(const segment_t *seg,uint8 number);
#endif	/* ECU_SEVEN_SEGMENT_H */

