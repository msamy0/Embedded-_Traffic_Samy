/*
* DIO implementation
* For practicing

*/
#include "dio.h"

void DIO_init(uint8_t pin_num, EN_port_name port_name, EN_pin_direction direction)
{
	switch (port_name)
	{
		case A:
			if (direction == OUT_pin)
			{
				DDRA_REG |= (1 << pin_num);
				break;
			}
			else if (direction == IN_pin)
			{
				DDRA_REG &=~ (1 << pin_num);
				break;
			}
			else
			{
				//Handel Error
				break;
			}

		case B:
			if (direction == OUT_pin)
			{
				DDRB_REG |= (1 << pin_num);
				break;
			}
			else if (direction == IN_pin)
			{
				DDRB_REG &= ~(1 << pin_num);
				break;
			}
			else
			{
				//Handel Error
				break;
			}
		case C:
			if (direction == OUT_pin)
			{
				DDRC_REG |= (1 << pin_num);
				break;
			}
			else if (direction == IN_pin)
			{
				DDRC_REG &= ~(1 << pin_num);
				break;
			}
			else
			{
				//Handel Error
				break;
			}

		case D:
			if (direction == OUT_pin)
			{
				DDRD_REG |= (1 << pin_num);
				break;
			}
			else if (direction == IN_pin)
			{
				DDRD_REG &= ~(1 << pin_num);
				break;
			}
			else
			{
				//Handel Error
				break;
			}

	}

}

void DIO_write(uint8_t pin_num, EN_port_name port_name, EN_pin_value value)
{
	switch (port_name)
	{
		case A:
			if (value == ON_value)
			{
				PORTA_REG |= (1 << pin_num);
				break;
			}
			else if (value == OFF_value)
			{
				PORTA_REG &= ~(1 << pin_num);
				break;
			}
			else
			{
				//Handel Error
				break;
			}

		case B:
			if (value == ON_value)
			{
				PORTB_REG |= (1 << pin_num);
				break;
			}
			else if (value == OFF_value)
			{
				PORTB_REG &= ~(1 << pin_num);
				break;
			}
			else
			{
				//Handel Error
				break;
			}

		case C:
			if (value == ON_value)
			{
				PORTC_REG |= (1 << pin_num);
				break;
			}
			else if (value == OFF_value)
			{
				PORTC_REG &= ~(1 << pin_num);
				break;
			}
			else
			{
				//Handel Error
				break;
			}

		case D:
			if (value == ON_value)
			{
				PORTD_REG |= (1 << pin_num);
				break;
			}
			else if (value == OFF_value)
			{
				PORTD_REG &= ~(1 << pin_num);
				break;
			}
			else
			{
				//Handel Error
				break;
			}
	}
}

void DIO_read(uint8_t pin_num, EN_port_name port_name, EN_pin_value* value)
{
	switch (port_name)
	{
		case A:
			if (((PINA_REG & (1 << pin_num)) >> pin_num))
			{
				*value = ON_value;
				break;
			}

			else if (!((PINA_REG & (1 << pin_num)) >> pin_num))
			{
				*value = OFF_value;
				break;
			}

			else
			{
				// Error handling
				break;
			}

		case B:
			if (((PINB_REG & (1 << pin_num)) >> pin_num))
			{
				*value = ON_value;
				break;
			}

			else if (!((PINB_REG & (1 << pin_num)) >> pin_num))
			{
				*value = OFF_value;
				break;
			}

			else
			{
				// Error handling
				break;
			}
		case C:
			if (((PINC_REG & (1 << pin_num)) >> pin_num))
			{
				*value = ON_value;
				break;
			}

			else if (!((PINC_REG & (1 << pin_num)) >> pin_num))
			{
				*value = OFF_value;
				break;
			}

			else
			{
				// Error handling
				break;
			}
		case D:
			if (((PIND_REG & (1 << pin_num)) >> pin_num))
			{
				*value = ON_value;
				break;
			}

			else if (!((PIND_REG & (1 << pin_num)) >> pin_num))
			{
				*value = OFF_value;
				break;
			}

			else
			{
				// Error handling
				break;
			}

	}
}

void DIO_toggle(uint8_t pin_num, EN_port_name port_name)
{

	EN_pin_value temp_value;
	DIO_read(pin_num, port_name, &temp_value);

	if (temp_value == OFF_value)
	{
		DIO_write(pin_num, port_name, OFF_value);
	}
	else if (temp_value == ON_value)
	{
		DIO_write(pin_num, port_name, ON_value);
	}
	else
	{
		//Error handle
	}

}
