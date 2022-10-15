/*
* DIO implementation
* For practicing
* Disclaimer : this timer driver could archive only accuracy up to (+/- 500 micro-second)
*/
#include "Timers.h"

static const ST_delay clear_delay = {0,0,0,0}; // used to clear delay structure before each initialization



TIMER_error_handler timer_init(EN_timer_num timer_num,EN_timer_interrupt timer_interrupt_init, EN_timer_prescaler prescaler, double delay_value, EN_delay_unit delay_unit)
{
	//terminate if delay is 0 
	if (delay_value <=0)
	{
		
		return TIMER_ERROR;
	}
	
	// interrupt enable or not 
	switch (timer_interrupt_init)
	{
		case interrupt_enable:
			switch (timer_num)
			{	
				case timer_0:
					TIMSK |= (1<<TOIE0);
					break;

				case timer_1:
					TIMSK |= (1<<TOIE1);
					break;
										
				case timer_2:
					TIMSK |= (1<<TOIE2);
					break;		
				default:
					return TIMER_ERROR;		
			}
			break;
				
		case interrupt_disable:
			switch (timer_num)
			{
				case timer_0:
					TIMSK &=~ (1<<TOIE0);
					break;

				case timer_1:
					TIMSK &=~ (1<<TOIE1);
					break;
										
				case timer_2:
					TIMSK &=~ (1<<TOIE2);
					break;
				default: 
					return TIMER_ERROR;
			}
			break;
			
	}
	
	// reset delay structure according to the timer being initialized 
		switch(timer_num)
	{	
		case timer_0:	
			delay_0 = clear_delay ;
			break;
		
		case timer_1:
			delay_1 = clear_delay ;
			break;
		
		case timer_2:
			delay_2 = clear_delay ;
			break;
			
		default:
			return TIMER_ERROR;
	}
	
	/* defining timer calculations variables*/
	uint16_t prescaler_value =1;
	double timer_size =256;
	double max_delay = 0;
	double n_overflow = 0;
	double timer_init_value = 0;
	double residual_buffer=0;
	double T_tick =0;
	
	/* timer size setting*/
	switch (timer_num)
	{
		case timer_0:
		{
			timer_size =256;
			break;
		}
		case timer_1:
		{
			timer_size =65536;
			break;
		}
		case timer_2:
		{
			timer_size =256;
			break;
		}
		
		default:
			return TIMER_ERROR;
	}
	
	/* converting delay units to micro-seconds as calcualtions are held in micro-seconds */
	switch (delay_unit)
	{
		case seconds:
			delay_value = delay_value*1000000;
			break;

		case millis:
			delay_value = delay_value * 1000;
			break;

		case micros:
			//do nothing, they are already in micro-seconds :D 
			break;
			
		default:
			return TIMER_ERROR;	
	}
	
	/* setting prescaler depending on the user choice, if automatic, then the could will evaluate it depending on the delay value*/
	switch (prescaler)
	{
		case automatic:
		{
			if (delay_value <= 1024)
			{
				prescaler_value = 1;
			}
			
			else if (delay_value > 1024 && delay_value <= 10240 )
			{
				prescaler_value = 8;
			}
			
			else if (delay_value > 10240 && delay_value <= 102400 )
			{
				prescaler_value = 64;
			}
			else if (delay_value > 102400 && delay_value <= 1024000 )
			{
				prescaler_value = 256;
			}
			else if (delay_value > 1024000 )
			{
				prescaler_value = 1024;
			}
			
			break;
		}
		
		case pre_1:
		{
			prescaler_value = 1;
			break;
		}	
		case pre_8:
		{
			prescaler_value = 8;
			break;
		}
		case pre_32:
		{
			prescaler_value = 32;
			break;
		}		
		case pre_64:
		{
			prescaler_value = 64;
			break;
		}
		case pre_128:
		{
			prescaler_value = 128;
			break;
		}		
		case pre_256:
		{
			prescaler_value = 256;
			break;
		}
		case pre_1024:
		{
			prescaler_value = 1024;
			break;
		}
		default:
			return TIMER_ERROR;
	}


	/*****************************************start timer math***********************************************/
	T_tick = ( ((double)prescaler_value) / (FCPU/1000000) );
	max_delay = timer_size * T_tick;

	if (max_delay >= delay_value)
	{
		timer_init_value = round((max_delay - delay_value) / T_tick);
	}
	
	else 
	{	
		residual_buffer = fmod(delay_value,max_delay);
		
		n_overflow = ((delay_value - residual_buffer)/max_delay) + 1 ; // (int)(delay/max_delay)
		timer_init_value = round(((max_delay - residual_buffer) / T_tick));
	}
	/*****************************************end timer math***********************************************/	
	switch (timer_num)
	{
		case timer_0:
			delay_0.init_value = timer_init_value;
			delay_0.n_overflow = n_overflow;
			delay_0.prescaler_value = prescaler_value;
			break;
		
		case timer_1:
			//delay_1.init_value = timer_init_value;
			//delay_1.n_overflow = n_overflow;
			//delay_1.prescaler_value = prescaler_value;
			break;
		
		case timer_2:
			delay_2.init_value = timer_init_value;
			delay_2.n_overflow = n_overflow;
			delay_2.prescaler_value = prescaler_value;
			break;		
		
		default:
			return TIMER_ERROR;
	}
return TIMER_OK;
}

TIMER_error_handler blocking_delay_0()
{
	TCNT0 = delay_0.init_value; // set time initial value
	switch (delay_0.prescaler_value)
	{
		case 1:
		{
			TCCR0|= (1<<CS00);
			break;
		}
		case 8:
		{
			TCCR0|= (1<<CS01);
			break;
		}
		case 64:
		{
			TCCR0|= (1<<CS01) | (1<<CS00) ;
			break;
		}
		case 256:
		{
			TCCR0|= (1<<CS02) ;
			break;
		}
		case 1024:
		{
			TCCR0|= (1<<CS02) | (1<<CS00) ;
			break;
		}
		default:
		{
			return TIMER_ERROR;
		}								
	}
	
	do
	{
		while((TIFR&0x01)==0 && stop_timer_0_flag == 0);
		TIFR = 0x1;
		delay_0.n_overflow_flag++;
	}
	while (delay_0.n_overflow_flag < (delay_0.n_overflow) && stop_timer_0_flag == 0);
	stop_timer_0_flag = 0;
		
	TCCR0 = 0x00;
	delay_0.n_overflow_flag = 0;
	return TIMER_OK;
}

TIMER_error_handler non_blocking_delay_2(EN_non_blocking_delay_status status)
{
	if (status == start)
	{
		TCNT2 = delay_2.init_value; // set time initial value
		switch (delay_2.prescaler_value)
		{
			case 1:
				TCCR2|= (1<<CS20);
				break;
		
			case 8:
				TCCR2|= (1<<CS21);
				break;
		
			case 32:
				TCCR2|= (1<<CS20) | (1<<CS21);
				break;
		
			case 64:
				TCCR2|= (1<<CS22) ;
				break;
		
			case 128:
				TCCR2|= (1<<CS20) | (1<<CS22) ;
				break;	
		
			case 256:
				TCCR2|= (1<<CS21) | (1<<CS22);
				break;
		
			case 1024:
				TCCR2|= (1<<CS20) | (1<<CS21) |(1<<CS22) ;
				break;
		
			default:
				return TIMER_ERROR;
		}
	}
	else if (status == stop)
	{
		
		TCCR2 = 0x00 ;
	}

	return TIMER_OK;
}

