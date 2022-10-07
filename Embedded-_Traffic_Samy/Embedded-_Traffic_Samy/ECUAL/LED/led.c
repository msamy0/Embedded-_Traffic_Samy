/*
LED Driver
By : Mohamed Samy
Date : 28/9/2022

*/
#include "led.h"

void LED_init(uint8_t led_pin, EN_port_name led_port)
{
	DIO_init(led_pin, led_port, OUT_pin);
}
void LED_on(uint8_t led_pin, EN_port_name led_port)
{
	DIO_write(led_pin, led_port, ON_value);
}
void LED_off(uint8_t led_pin, EN_port_name led_port)
{
	DIO_write(led_pin, led_port, OFF_value);
}
void LED_toggle(uint8_t led_pin, EN_port_name led_port)
{
	DIO_toggle(led_pin, led_port);
}
void LED_blink_start(uint8_t led_pin, EN_port_name led_port)
{
	DIO_write(led_pin, led_port, ON_value);
	non_blocking_delay_2(start);
}
void LED_blink_stop(uint8_t led_pin, EN_port_name led_port)
{
	DIO_write(led_pin, led_port, OFF_value);
	non_blocking_delay_2(stop);	
}
