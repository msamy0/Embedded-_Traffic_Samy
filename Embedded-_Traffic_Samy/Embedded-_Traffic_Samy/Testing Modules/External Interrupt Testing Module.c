/*
External interrupt module test 
 */ 

#include "../MCAL/Interrups/Interrupts.h"
#define INT_NUM 0

uint8_t flag = 0;

int main(void)
{

    global_interrupt_init();
	external_interrupt_sense_mode(INT_NUM,falling_edge);
	external_interrupt_init(INT_NUM);
	
	DDRA |= (1<<2);
	DDRD &=~ (1<<2);
	
    while (1) 
	{
		switch (flag)
			{
				case 1:
				{
					PORTA |= (1<<2);
					break;	
				}
				case 0:
				{
					PORTA &=~ (1<<2);
					break;
				}
				
			}
	}

}

ISR(INT0_vect)
{
	if (flag == 1)
	{
		flag = 0;
	}
	else
	{
		flag = 1;
	}
}

