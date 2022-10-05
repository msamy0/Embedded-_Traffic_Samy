/*
* DIO implementation
* For practicing
* Disclaimer : this timer driver could archive only accuracy up to (+/- 500 micro-second)
*/
#include "Timers.h"

static const ST_delay clear_delay = {0,0,0,0}; // used to clear delay structure before each initialization
volatile ST_delay delay_0;


void timer_init(EN_timer_num timer_num, EN_timer_prescaler prescaler, double delay_value, EN_delay_unit delay_unit)
{
	delay_0 = clear_delay ;
	
	if (delay_value <=0)
	{
		return;
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
	}
	
	/* converting delay units to micro-seconds */
	switch (delay_unit)
	{
		case seconds:
		{
			delay_value = delay_value*1000000;
			break;
		}

		case millis:
		{
			delay_value = delay_value * 1000;
			break;
		}
		case micros:
		{
			//do nothing, they are already in micro-seconds :D 
			break;
		}

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
		case pre_64:
		{
			prescaler_value = 64;
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
		{
			delay_0.init_value = timer_init_value;
			delay_0.n_overflow = n_overflow;
			delay_0.prescaler_value = prescaler_value;
			break;
		}
		case timer_1:
		{
			//delay_1.init_value = timer_init_value;
			//delay_1.n_overflow = n_overflow;
			//delay_1.prescaler_value = prescaler_value;
			break;
		}
		case timer_2:
		{
			//delay_2.init_value = timer_init_value;
			//delay_2.n_overflow = n_overflow;
			//delay_2.prescaler_value = prescaler_value;
			break;
		}		
	}

}

void blocking_delay_0()
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
			TCCR0|= (1<<CS01);;
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
			TCCR0|= (1<<CS00);
			break;	
		}								
	}
	
	do
	{
		while((TIFR&0x01)==0);
		TIFR = 0x1;
		delay_0.n_overflow_flag++;
	}
	while (delay_0.n_overflow_flag < (delay_0.n_overflow) );

	TCCR0 = 0x00;
	delay_0.n_overflow_flag = 0;
	
}

/*
void timer_calculations_compensation()
{
//run timer to calculate delay initialization and math calculation execution period
//to subtract it later to the delay value.
TCNT0 = 0x00;	// Timer0 - initial value 0
TCCR0 = 0x02;	// Timer0 - normal mode - prescaler 8
volatile uint8_t  excution_stopwatch=0; // store the TCNT0 spent period before delay actually starts
volatile uint16_t excution_micros=0;	// value to be subtracted from delay_value						
//get value of stopwatch running from the beginning of the function execution
if( (TIFR & 0x01) == 1)
{
	TIFR = 0x01;
	excution_stopwatch = TCNT0;
	excution_micros = (256 + excution_stopwatch) * 8;
}

else
{
	excution_stopwatch = TCNT0;
	excution_micros = excution_stopwatch * 8;
}
TCCR0 = 0x00;
}
*/
