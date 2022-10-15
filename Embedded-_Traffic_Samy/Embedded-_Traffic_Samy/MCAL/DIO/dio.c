/*
* DIO implementation
* For practicing

*/
#include "dio.h"

DIO_error_handler DIO_init(uint8_t pin_num, EN_port_name port_name, EN_pin_direction direction)
{
	if (pin_num <0 || pin_num >7)
	{
		return PIN_NUM_ERROR;
	}
	else
	{	
		switch (port_name)
		{
			case A:
				if (direction == OUT_pin)
				{
					DDRA |= (1 << pin_num);
					break;
				}
				else if (direction == IN_pin)
				{
					DDRA &=~ (1 << pin_num);
					break;
				}
				else
				{
					return VALUE_ERROR;
				}

			case B:
				if (direction == OUT_pin)
				{
					DDRB |= (1 << pin_num);
					break;
				}
				else if (direction == IN_pin)
				{
					DDRB &= ~(1 << pin_num);
					break;
				}
				else
				{
					return VALUE_ERROR;
				}
			case C:
				if (direction == OUT_pin)
				{
					DDRC |= (1 << pin_num);
					break;
				}
				else if (direction == IN_pin)
				{
					DDRC &= ~(1 << pin_num);
					break;
				}
				else
				{
					return VALUE_ERROR;
				}

			case D:
				if (direction == OUT_pin)
				{
					DDRD |= (1 << pin_num);
					break;
				}
				else if (direction == IN_pin)
				{
					DDRD &= ~(1 << pin_num);
					break;
				}
				else
				{
					return VALUE_ERROR;
				}
			
			default:
					return PORT_NAME_ERROR;
		}
	}
 return DIO_OK;
}

DIO_error_handler DIO_write(uint8_t pin_num, EN_port_name port_name, EN_pin_value value)
{
	if (pin_num <0 || pin_num >7)
	{
		return PIN_NUM_ERROR;
	}
	else
	{
		switch (port_name)
		{
			case A:
				if (value == ON_value)
				{
					PORTA |= (1 << pin_num);
					break;
				}
				else if (value == OFF_value)
				{
					PORTA &= ~(1 << pin_num);
					break;
				}
				else
				{
					//Handel Error
					return VALUE_ERROR;
				}

			case B:
				if (value == ON_value)
				{
					PORTB |= (1 << pin_num);
					break;
				}
				else if (value == OFF_value)
				{
					PORTB &= ~(1 << pin_num);
					break;
				}
				else
				{
					//Handel Error
					return VALUE_ERROR;
				}

			case C:
				if (value == ON_value)
				{
					PORTC |= (1 << pin_num);
					return PORT_NAME_ERROR;
				}
				else if (value == OFF_value)
				{
					PORTC &= ~(1 << pin_num);
					break;
				}
				else
				{
					//Handel Error
					return VALUE_ERROR;
				}

			case D:
				if (value == ON_value)
				{
					PORTD |= (1 << pin_num);
					break;
				}
				else if (value == OFF_value)
				{
					PORTD &= ~(1 << pin_num);
					break;
				}
				else
				{
					//Handel Error
					return VALUE_ERROR;
				}
			default:
				return PORT_NAME_ERROR ;
		}
	}
	return DIO_OK;
}

DIO_error_handler DIO_write_port(EN_port_name port_name, EN_pin_value value)
{
	
	switch (port_name)
	{
		case A:
			if (value == ON_value)
			{
				PORTA = 0xff;
			}
			else if (value == OFF_value)
			{
				PORTA = 0x00;
			}
			else
			{
				return VALUE_ERROR;
			}
			break;
		case B:
			if (value == ON_value)
			{
				PORTA = 0xff;
			}
			else if (value == OFF_value)
			{
				PORTA = 0x00;
			}
			else
			{
				return VALUE_ERROR;
			}
			break;
		case C:
			if (value == ON_value)
			{
				PORTA = 0xff;
			}
			else if (value == OFF_value)
			{
				PORTA = 0x00;
			}
			else
			{
				return VALUE_ERROR;
			}
			break;
		case D:
			if (value == ON_value)
			{
				PORTA = 0xff;
			}
			else if (value == OFF_value)
			{
				PORTA = 0x00;
			}
			else
			{
				return VALUE_ERROR;
			}
			break;
		default:
			return PORT_NAME_ERROR;
	}
	return DIO_OK;
}

DIO_error_handler DIO_read(uint8_t pin_num, EN_port_name port_name, EN_pin_value* value)
{
	if (pin_num <0 || pin_num >7)
	{
		return PIN_NUM_ERROR;
	}
	else
	{
		switch (port_name)
		{
			case A:
				if (((PINA & (1 << pin_num)) >> pin_num))
				{
					*value = ON_value;
					break;
				}

				else if (!((PINA & (1 << pin_num)) >> pin_num))
				{
					*value = OFF_value;
					break;
				}

				else
				{
					// Error handling
					return PIN_NUM_ERROR;
				}

			case B:
				if (((PINB & (1 << pin_num)) >> pin_num))
				{
					*value = ON_value;
					break;
				}

				else if (!((PINB & (1 << pin_num)) >> pin_num))
				{
					*value = OFF_value;
					break;
				}

				else
				{
					// Error handling
					return PIN_NUM_ERROR;
				}
			case C:
				if (((PINC & (1 << pin_num)) >> pin_num))
				{
					*value = ON_value;
					break;
				}

				else if (!((PINC & (1 << pin_num)) >> pin_num))
				{
					*value = OFF_value;
					break;
				}

				else
				{
					// Error handling
					return PIN_NUM_ERROR;
				}
			case D:
				if (((PIND & (1 << pin_num)) >> pin_num))
				{
					*value = ON_value;
					break;
				}

				else if (!((PIND & (1 << pin_num)) >> pin_num))
				{
					*value = OFF_value;
					break;
				}

				else
				{
					// Error handling
					return PIN_NUM_ERROR;
				}
			default:
				return PORT_NAME_ERROR;

		}
	}
	return DIO_OK;

}

DIO_error_handler DIO_toggle(uint8_t pin_num, EN_port_name port_name)
{
	if (pin_num <0 || pin_num >7)
	{
		return PIN_NUM_ERROR;
	}
	else
	{	
		switch (port_name)
		{
			case A:
				PORTA ^= (1<<pin_num);
				break;
		
			case B:
				PORTB ^= (1<<pin_num);
				break;

			case C:
				PORTC ^= (1<<pin_num);
				break;

			case D:
				PORTD ^= (1<<pin_num);
				break;
				
			default:
				return PORT_NAME_ERROR;				
		}
	}
	return DIO_OK;
}


