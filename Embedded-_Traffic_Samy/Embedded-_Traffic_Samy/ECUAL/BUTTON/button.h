#ifndef BUTTON_H_
#define BUTTON_H_
#include "../../Utilities/typedefs.h"
#include "../../MCAL/DIO/dio.h"

void Button_init(uint8_t button_pin, EN_port_name button_port);

void button_read(uint8_t button_pin, EN_port_name button_port, EN_pin_value *value);


#endif