#ifndef DIO_H_
#define DIO_H_

#include "../../Utilities/typedefs.h"
#include <avr/io.h>
	
#define TOGGLE(PORT,PIN) (PORT ^=  (1<<PIN))

typedef enum EN_port_name {A,B,C,D} EN_port_name;
	
typedef enum EN_pin_direction {IN_pin,OUT_pin} EN_pin_direction;
	
typedef enum EN_pin_value {OFF_value,ON_value} EN_pin_value;

typedef enum DIO_error_handler {DIO_OK,PIN_NUM_ERROR,PORT_NAME_ERROR,VALUE_ERROR} DIO_error_handler;


DIO_error_handler DIO_init(uint8_t pinNum, EN_port_name port_name, EN_pin_direction direction);

DIO_error_handler DIO_write(uint8_t pinNum, EN_port_name port_name, EN_pin_value value);

DIO_error_handler DIO_write_port(EN_port_name port_name, EN_pin_value value);

DIO_error_handler DIO_read(uint8_t pinNum, EN_port_name port_name,  EN_pin_value *value);

DIO_error_handler DIO_toggle(uint8_t pinNum, EN_port_name port_name);


#endif



/*#define PORTA *((volatile uint8_t*)(0x3B))
#define DDRA *((volatile uint8_t*)(0x3A))
#define PINA *((volatile uint8_t*)(0x39))

#define PORTB *((volatile uint8_t*)(0x38))
#define DDRB *((volatile uint8_t*)(0x37))
#define PINB *((volatile uint8_t*)(0x36))

#define PORTC *((volatile uint8_t*)(0x35))
#define DDRC *((volatile uint8_t*)(0x34))
#define PINC *((volatile uint8_t*)(0x33))

#define PORTD *((volatile uint8_t*)(0x32))
#define DDRD *((volatile uint8_t*)(0x31))
#define PIND *((volatile uint8_t*)(0x30))*/