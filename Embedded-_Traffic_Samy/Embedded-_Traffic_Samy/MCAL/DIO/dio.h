#ifndef DIO_H_
#define DIO_H_

#include "../../Utilities/typedefs.h"
#include "../../Utilities/registers.h"

typedef enum EN_port_name {A,B,C,D} EN_port_name;
	
typedef enum EN_pin_direction {IN_pin,OUT_pin} EN_pin_direction;
	
typedef enum EN_pin_value {OFF_value,ON_value} EN_pin_value;


void DIO_init(uint8_t pinNum, EN_port_name portNum, EN_pin_direction direction);

void DIO_write(uint8_t pinNum, EN_port_name portNum, EN_pin_value value);

void DIO_read(uint8_t pinNum, EN_port_name portNum,  EN_pin_value *value);

void DIO_toggle(uint8_t pinNum, EN_port_name portNum);


#endif