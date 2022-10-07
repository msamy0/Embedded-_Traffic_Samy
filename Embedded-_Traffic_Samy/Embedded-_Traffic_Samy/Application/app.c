/*
 * app.c
 *
 * Created: 25/09/2022 03:58:51 م
 *  Author: mohsa
 */ 
#include "app.h"



void app_init() {
	/* traffic LED initializations */
	LED_init(CAR_RED_LED_PIN, LEDs_PORT);
	LED_init(CAR_GREEN_LED_PIN, LEDs_PORT);
	LED_init(CAR_YELLOW_LED_PIN, LEDs_PORT);
	LED_init(PERSON_RED_LED_PIN, LEDs_PORT);
	LED_init(PERSON_GREEN_LED_PIN, LEDs_PORT);
	LED_init(PERSON_YELLOW_LED_PIN, LEDs_PORT);
	
	/* pedestrian leds initialization */
	LED_init(PEDESTRIAN_LED_PIN,PEDESTRIAN_LED_PORT);
	
	/* Global interrupts initialization*/
	sei();
	external_interrupt_sense_mode(BUTTON_INTERRUPT_NUM,rising_edge);
	external_interrupt_init(BUTTON_INTERRUPT_NUM);

	/*timer initialization*/
	timer_init(timer_0,interrupt_disable,automatic,TRAFFIC_INTERVAL,millis);
	timer_init(timer_2,interrupt_enable,pre_1,Y_B_INTERVAL,millis);
	
	/*init all variables status*/
	traffic_status_mask = MODE_1_MASK;
	stop_timer_0_flag = 0;
	pedstrain_press_flag = 0;
	pedstrain_mode_flag = 0;
	in_delay_flag = 0;
	turn_off_all_leds();
}

void app_start()
{
	while(1) // loop infinite
	{
		traffic_mode_1_CR_PG(); //car_red_led + pedestrian_green_led
		traffic_mode_2_CRY_PGY();
		traffic_mode_3_CG_PR();
		traffic_mode_4_CGY_PRY();
	}
}

void turn_off_all_leds() // function to turn off every thing
{
DIO_write_port(LEDs_PORT,OFF_value);
LED_blink_stop(CAR_YELLOW_LED_PIN,LEDs_PORT);
LED_blink_stop(PERSON_YELLOW_LED_PIN,LEDs_PORT);
}

void traffic_mode_1_CR_PG()
{	
	/* check whether to execute this function or exit depending on the current mask*/
	if(traffic_status_mask != MODE_1_MASK)
	{
		return;
	}
	else
	{
		
		turn_off_all_leds();//erase last mode condition
		LED_on(CAR_RED_LED_PIN,LEDs_PORT);
		LED_on(PERSON_GREEN_LED_PIN,LEDs_PORT);

		in_delay_flag = 1; // flag that let the ISR0 that code is in loop now
		blocking_delay_0(); //do busy wait holding current led status
		in_delay_flag = 0;
		
		/*this condition will be true if pedestrian is pressed in the last delay*/
		if (pedstrain_press_flag ==1 && pedstrain_mode_flag == 1)
		{
			//if yes, clear the press_flag and let mode_flag on until we finish a full pedestrian loop
			pedstrain_press_flag = 0;
			traffic_status_mask = MODE_2_MASK; // return to mode_1 as we have a pedestrian want to pass
		}
		else
		{
			traffic_status_mask = MODE_2_MASK;//move to the next logical mode as a normal traffic light
		}	
	}
}

void traffic_mode_2_CRY_PGY()
{
	if(traffic_status_mask != MODE_2_MASK)
	{
		return;
	}
	else
	{
		
		turn_off_all_leds();
		LED_on(CAR_RED_LED_PIN,LEDs_PORT);
		LED_blink_start(CAR_YELLOW_LED_PIN,LEDs_PORT);
		LED_on(PERSON_GREEN_LED_PIN,LEDs_PORT);
		LED_blink_start(PERSON_YELLOW_LED_PIN,LEDs_PORT);
		
		in_delay_flag = 1;
		blocking_delay_0();
		in_delay_flag = 0;
		
		if (pedstrain_press_flag ==1 && pedstrain_mode_flag == 1)
		{
			pedstrain_press_flag =0;
			traffic_status_mask = MODE_1_MASK;
		}
		else
		{
			traffic_status_mask = MODE_3_MASK;
		}
	}
}

void traffic_mode_3_CG_PR()
{
	if(traffic_status_mask != 0b00010100)
	{
		return;
	}
	else
	{
		
		turn_off_all_leds();
		LED_on(CAR_GREEN_LED_PIN,LEDs_PORT);
		LED_on(PERSON_RED_LED_PIN,LEDs_PORT);
		
		/*reaching mode 3 means the pedestrian loop is finished, so clear pedestrian_mode_flag*/
		pedstrain_mode_flag = 0;
		PORTB &=~ (1<<0);
		
		in_delay_flag = 1;
		blocking_delay_0();
		in_delay_flag = 0;
		
		if (pedstrain_press_flag ==1 && pedstrain_mode_flag == 1)
		{
			pedstrain_press_flag =0;
			traffic_status_mask = MODE_4_MASK;
		}
		else
		{
			traffic_status_mask = MODE_4_MASK;
		}
		
		
	}
}

void traffic_mode_4_CGY_PRY()
{
	if(traffic_status_mask != MODE_4_MASK)
	{
		return;
	}
	else
	{
		
		turn_off_all_leds();
		LED_on(CAR_GREEN_LED_PIN,LEDs_PORT);
		LED_blink_start(CAR_YELLOW_LED_PIN,LEDs_PORT);
		LED_on(PERSON_RED_LED_PIN,LEDs_PORT);
		LED_blink_start(PERSON_YELLOW_LED_PIN,LEDs_PORT);
		
		in_delay_flag = 1;
		blocking_delay_0();
		in_delay_flag = 0;

		if (pedstrain_press_flag ==1 && pedstrain_mode_flag == 1)
		{
			pedstrain_press_flag =0;
			traffic_status_mask = MODE_1_MASK;
		}
		else
		{
			traffic_status_mask = MODE_1_MASK;
		}
	}
}

ISR(INT0_vect)//pedestrian button
{
	if (!pedstrain_mode_flag && in_delay_flag)//only work if it is not in pedestrian mode and in delay
	{
		pedstrain_press_flag = 1 ; //raise flags 
		pedstrain_mode_flag = 1 ;
		PEDESTRIAN_LED_PORT_REG |= (1<<PEDESTRIAN_LED_PIN);//for debugging, turn on pedestrian mode led 
		
		/*raise stop_timer_0_flag to exit any busy wait delay (blocking delay)*/
		if(traffic_status_mask !=MODE_4_MASK && traffic_status_mask !=MODE_1_MASK )
		{
			stop_timer_0_flag =1;
		}
	}
}

/*this timer_2 over flow flag used in blink timing for the yellow leds*/
ISR(TIMER2_OVF_vect)
{
	delay_2.n_overflow_flag++;
	if (delay_2.n_overflow_flag >= delay_2.n_overflow)
	{
		LEDs_PORT_REG ^= (1<<CAR_YELLOW_LED_PIN) ^ (1<<PERSON_YELLOW_LED_PIN);
		delay_2.n_overflow_flag =0;	
	}
}