/* 
 * File:   hal_gpio.c
 * Author: NAGHM.A.O
 *
 * Created on 14 March 2024, 20:09
 */

#include "hal_gpio.h"

volatile uint8 *tris_register[] ={&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
volatile uint8 *lat_register[]  ={&LATA, &LATB, &LATC, &LATD, &LATE};
volatile uint8 *port_register[] ={&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

#if GPIO_PORT_PIN_CONFIG == config_ENABLE
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *pin_config){
    Std_ReturnType ret = E_OK;
    if((NULL==pin_config)|| ((pin_config->pin)>PIN_MAX_NUMBER-1)){
        ret = E_NOK;
    }
    else{
    switch (pin_config->direction) {
        case GPIO_Output_direction:
            CLEAR_BIT(*tris_register[pin_config->port],pin_config->pin);
            break;

        case GPIO_Input_direction:
            SET_BIT(*tris_register[pin_config->port],pin_config->pin);

            break;
            
        default: ret= E_NOK;
    }
    }
    return (ret);
}
#endif

#if GPIO_PORT_PIN_CONFIG == config_ENABLE
Std_ReturnType gpio_pin_get_direction_intialize(const pin_config_t *pin_config, direction_t *direction_stat){
    Std_ReturnType ret = E_OK;
    if((NULL==pin_config)||(NULL==direction_stat)||((pin_config->pin)>PIN_MAX_NUMBER-1)){
        ret = E_NOK;
    }
    else{
        *direction_stat = READ_BIT(*tris_register[pin_config->port],pin_config->pin);
    }
      return (ret);
}
#endif

#if GPIO_PORT_PIN_CONFIG == config_ENABLE
Std_ReturnType gpio_pin_write_logic(const pin_config_t *pin_config, logic_t logic){
    Std_ReturnType ret = E_OK;
    if((NULL==pin_config)||((pin_config->pin)>PIN_MAX_NUMBER-1)){
        ret = E_NOK;
    }
    else{
         switch (logic) {
        case GPIO_LOW:
            CLEAR_BIT(*lat_register[pin_config->port],pin_config->pin);
            break;

        case GPIO_HIGH:
            SET_BIT(*lat_register[pin_config->port],pin_config->pin);
            break;
            
        default: ret= E_NOK;
    }
    }
      return (ret);
}
#endif

#if GPIO_PORT_PIN_CONFIG == config_ENABLE
Std_ReturnType gpio_pin_read_logic(const pin_config_t *pin_config, logic_t *logic){
    Std_ReturnType ret = E_OK;
    if((NULL==pin_config)||(NULL==logic)||((pin_config->pin)>PIN_MAX_NUMBER-1)){
        ret = E_NOK;
    }
    else{
       *logic = READ_BIT(*port_register[pin_config->port],pin_config->pin);
    }
      return (ret);
}
#endif

#if GPIO_PORT_PIN_CONFIG == config_ENABLE
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *pin_config){
     Std_ReturnType ret = E_OK;
    if((NULL==pin_config)||((pin_config->pin)>PIN_MAX_NUMBER-1)){
        ret = E_NOK;
    }
    else{
        TOGGLE_BIT(*lat_register[pin_config->port],pin_config->pin);
    }
      return (ret);
}
#endif

#if GPIO_PORT_PIN_CONFIG == config_ENABLE
Std_ReturnType gpio_pin_intialize(const pin_config_t *pin_config){
 Std_ReturnType ret = E_OK;
    if((NULL==pin_config)||((pin_config->pin)>PIN_MAX_NUMBER-1)){
        ret = E_NOK;
    }
    else{
        ret = gpio_pin_direction_intialize(pin_config);
        ret = gpio_pin_write_logic(pin_config, pin_config->logic);
    }
      return (ret);

}
#endif

#if GPIO_PORT_PIN_CONFIG == config_ENABLE
Std_ReturnType gpio_port_direction_intialize(Port_index_t port, uint8 direction){
     Std_ReturnType ret = E_OK;
     if(port> PORT_MAX_NUMBER-1){
         ret= E_NOK;
     }
     else {
         *tris_register[port]= direction;
     }
    
      return (ret);
}
#endif

#if GPIO_PORT_CONFIG == config_ENABLE
Std_ReturnType gpio_port_get_direction_intialize(Port_index_t port, uint8 *direction_stat){
    Std_ReturnType ret = E_OK;
    if((NULL== direction_stat)&&(port> PORT_MAX_NUMBER-1)){
                 ret= E_NOK;
    }
    else{
        *direction_stat = *tris_register[port];
    }
    
      return (ret);
}
#endif

#if GPIO_PORT_CONFIG == config_ENABLE
Std_ReturnType gpio_port_write_logic(Port_index_t port, logic_t logic){
    Std_ReturnType ret = E_OK;
     if(port> PORT_MAX_NUMBER-1){
                 ret= E_NOK;
    }
     else{
         *lat_register[port]= logic;
     }
    
      return (ret);
}
#endif

#if GPIO_PORT_CONFIG == config_ENABLE
Std_ReturnType gpio_port_read_logic(Port_index_t port, logic_t *logic){
    Std_ReturnType ret = E_OK;
    if((NULL== logic)&&(port> PORT_MAX_NUMBER-1)){
                 ret= E_NOK;
    }
    else{
        *logic= *lat_register[port];
    }
    
      return (ret);
}
#endif

#if GPIO_PORT_CONFIG == config_ENABLE
Std_ReturnType gpio_port_toggle_logic(Port_index_t port){
    Std_ReturnType ret = E_OK;
    if(port> PORT_MAX_NUMBER-1){
                 ret= E_NOK;
    }
    else{
        *lat_register[port]^= PORT_MASK;
    }
    
      return (ret);
}
#endif


