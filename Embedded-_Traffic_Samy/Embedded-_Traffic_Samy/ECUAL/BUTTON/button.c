/*
* button.c file 
created : 
author : mohamed Samy

*/

#include "button.h"

void Button_init(uint8_t button_pin, EN_port_name button_port)
{	
	DIO_init(button_pin,button_port,IN_pin);
}

void button_read(uint8_t button_pin, EN_port_name button_port, EN_pin_value *value)
{
DIO_read(button_pin, button_port, value);	
}

