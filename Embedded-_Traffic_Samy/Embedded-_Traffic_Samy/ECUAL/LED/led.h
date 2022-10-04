#ifndef LED_H_
#define LED_H_

#include "../../Utilities/typedefs.h"
#include "../../MCAL/DIO/dio.h"

void LED_init(uint8_t led_pin, EN_port_name led_port );
void LED_on(uint8_t led_pin, EN_port_name led_port );
void LED_off(uint8_t led_pin, EN_port_name led_port );
void LED_toggle(uint8_t led_pin, EN_port_name led_port );


#endif