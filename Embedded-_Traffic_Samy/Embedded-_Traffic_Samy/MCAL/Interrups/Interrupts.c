/*
* DIO implementation
* For practicing

*/
#include "Interrupts.h"


void global_interrupt_init()
{
	// function from avr/intterupt.h library that sets the global interrupt enabled
	sei();
}

void external_interrupt_sense_mode(uint8_t interrupt_num,  INT_sense_mode mode)
{
	switch (interrupt_num)
	{
		/***********************************************/
		case 0: //in case user chose External interrupt 0
			if (mode == rising_edge)
			{
				MCUCR |= (1<<ISC00) | (1<<ISC01);//setting (MCU Control Register Bit-0 and Bit-1) for rising edge mode
				break;
			}
			else if (mode == falling_edge)
			{
				MCUCR &= ~(1<<ISC00);//setting (MCU Control Register Bit-0 and Bit-1) for falling edge mode
				MCUCR |= (1<<ISC01); 
				
				break;
			}
			
			else if (mode == logic_change)
			{
				MCUCR |= (1<<ISC00);//setting (MCU Control Register Bit-0 and Bit-1) for logic change mode
				MCUCR &= ~(1<<ISC01);
				
				break;
			}
			
			else if (mode == low_level)
			{
				MCUCR &= ~(1<<ISC00); //setting (MCU Control Register Bit-0 and Bit-1) for low_level mode
				MCUCR &= ~(1<<ISC01);
				break;
			}
			else
			{
				//error handling
				break;
			}
			
		/***********************************************/
		case 1: //in case user chose External interrupt 1
			if (mode == rising_edge)
			{
				MCUCR |= (1<<ISC10) | (1<<ISC11);	//setting (MCU Control Register Bit-2 and Bit-3) for rising edge mode
				break;
			}
			else if (mode == falling_edge)
			{
				MCUCR &= ~(1<<ISC10); //setting (MCU Control Register Bit-2 and Bit-3) for falling edge mode
				MCUCR |= (1<<ISC11); 
				break;
			}
		
			else if (mode == logic_change)
			{
				MCUCR |= (1<<ISC10); //setting (MCU Control Register Bit-2 and Bit-3) for logic change mode
				MCUCR &= ~(1<<ISC11);
				break;
			}
		
			else if (mode == low_level)
			{
				MCUCR &= ~(1<<ISC10); //setting (MCU Control Register Bit-2 and Bit-3) for low_level mode
				MCUCR &= ~(1<<ISC11);
				break;
			}
			else
			{
				//error handling
				break;
			}
		
		/***********************************************/
		case 2: //in case user chose External interrupt 2
			if (mode == rising_edge)
			{
				MCUCSR |= (1<<ISC2);	//setting (MCUCSR Bit-6) for rising edge mode
				break;
			}
			else if (mode == falling_edge)
			{
				MCUCSR &= ~(1<<ISC2); //setting (MCUCSR Bit-6) for falling edge mode
				break;
			}
		
			else if (mode == logic_change || mode == low_level)
			{
				/*force setting (MCUCSR Bit-6) for rising edge mode
				as logic change and low level modes are not options for EXT_INT2*/
				MCUCSR |= (1<<ISC2);	
				//show warning to the user for that miss_implementation
				break;
			}
		
			else
			{
				//error handling
				break;
			}
	}
}


void external_interrupt_init(uint8_t interrupt_num)
{
	switch (interrupt_num)
	{
		case 0:
		{
			GICR |= 1<<6; //setting bit-6 in GICR register HIGH to enable interrupt 0
			break;
		}
		case 1:
		{
			GICR |= (1<<INT1);//setting bit-7 in GICR register HIGH to enable interrupt 1
			break;
		}
		case 2:
		{
			GICR |= (1<<INT2);//setting bit-5 in GICR register HIGH to enable interrupt 2
			break;
		}	
	}
}

