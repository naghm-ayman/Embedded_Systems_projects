/* 
 * File:   hal_gpio.h
 * Author: NAGHM.A.O
 *
 * Created on 14 March 2024, 20:09
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/*section of INCLUDES */
#include "pic18f4620.h"
#include"../mcal_std_types.h"
#include"../device_config.h"
#include"hal_gpio_cfg.h"

/*section of MACRO DECLARATIONS */
#define BIT_MASK    (uint8)1
#define PIN_MAX_NUMBER  8
#define PORT_MAX_NUMBER  5
#define PORT_MASK       0xFF

#define GPIO_PORT_PIN_CONFIG  config_ENABLE
#define GPIO_PORT_CONFIG      config_ENABLE


/*section of MACRO FUNCTIONS DECLARATIONS */
#define SET_BIT(REG,BIT_POSN)      (REG |=(BIT_MASK << BIT_POSN))
#define CLEAR_BIT(REG,BIT_POSN)    (REG &= ~(BIT_MASK << BIT_POSN))
#define TOGGLE_BIT(REG,BIT_POSN)   (REG ^=(BIT_MASK << BIT_POSN))
#define READ_BIT(REG,BIT_POSN)     ((REG >> BIT_POSN)& BIT_MASK)

typedef enum{
    GPIO_LOW,
    GPIO_HIGH
}logic_t;

typedef enum{
    GPIO_Output_direction,
    GPIO_Input_direction
}direction_t;

typedef enum{
    GPIO_Pin0,
    GPIO_Pin1,
    GPIO_Pin2,
    GPIO_Pin3,
    GPIO_Pin4,
    GPIO_Pin5,
    GPIO_Pin6,
    GPIO_Pin7,
}Pin_index_t;

typedef enum{
    PortA_index,
    PortB_index,
    PortC_index,
    PortD_index,         
    PortE_index,
}Port_index_t;

typedef struct{
    uint8 port:3;        /* @ref Port_index_t */
    uint8 pin :3;        /* @ref Pin_index_t */
    uint8 direction :1;  /* @ref direction_t */
    uint8 logic :1;      /* @ref logic_t */
}pin_config_t;

/*section of MACRO DECLARATIONS */


/*section of FUNCTIONS DECLARATIONS */
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *pin_config);
Std_ReturnType gpio_pin_get_direction_intialize(const pin_config_t *pin_config, direction_t *direction_stat);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *pin_config, logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t *pin_config, logic_t *logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *pin_config);
Std_ReturnType gpio_pin_intialize(const pin_config_t *pin_config);

Std_ReturnType gpio_port_direction_intialize(Port_index_t port, uint8 direction);
Std_ReturnType gpio_port_get_direction_intialize(Port_index_t port, uint8 *direction_stat);
Std_ReturnType gpio_port_write_logic(Port_index_t port, logic_t logic);
Std_ReturnType gpio_port_read_logic(Port_index_t port, logic_t *logic);
Std_ReturnType gpio_port_toggle_logic(Port_index_t port);


#endif	/* HAL_GPIO_H */

