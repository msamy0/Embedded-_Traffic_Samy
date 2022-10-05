/*
 * Timer_Testing_Module.c
 *
 * Created: 04/10/2022 09:05:51 م
 *  Author: mohsa
 */ 
#include "../MCAL/Timers/Timers.h"
#include "../MCAL/DIO/dio.h"

#define TEST_DIO_PIN 3
#define TEST_DIO_PORT B

extern ST_delay delay_0;

int Timer_Testing_0 (void)
{
	DIO_init(TEST_DIO_PIN,TEST_DIO_PORT,OUT_pin);
	DIO_write(TEST_DIO_PIN,TEST_DIO_PORT,OFF_value);
	
	timer_init(timer_0,automatic,200,millis);
	
	
	while (1)
	{
		
		blocking_delay_0();
		
		DIO_toggle(TEST_DIO_PIN,TEST_DIO_PORT);	
	}
	return 0;
}