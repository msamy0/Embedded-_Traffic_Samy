#ifndef APP_H_
#define APP_H_

#include "../ECUAL/BUTTON/button.h"
#include "../ECUAL/LED/led.h"
#include "../MCAL/Interrups/Interrupts.h"
#include "../MCAL/Timers/Timers.h"

/* define ports and pins for traffic leds used*/
#define LEDs_PORT A
#define LEDs_PORT_REG PORTA

#define CAR_RED_LED_PIN 1
#define CAR_YELLOW_LED_PIN 2
#define CAR_GREEN_LED_PIN 3

#define PERSON_RED_LED_PIN 4
#define PERSON_YELLOW_LED_PIN 5
#define PERSON_GREEN_LED_PIN 6

/*define pin and port for pedstrain led indicator*/
#define PEDESTRIAN_LED_PIN 0
#define PEDESTRIAN_LED_PORT B
#define PEDESTRIAN_LED_PORT_REG PORTB

/*define interrupt connection button*/
#define BUTTON_INTERRUPT_NUM 0

/* define intervals used in application*/
#define TRAFFIC_INTERVAL 5000
#define Y_B_INTERVAL 50 //Yellow blink interval

/*
* traffic_status_mask illustrated (C>car	P>person	R>red
* G>green		Y>yellow	RY>red with blinking yellow		GY>green with blinking yellow)
*	7		6		5		4		3		2		1		0
	PGY		PG		PRY		PR		CGY		CG		CRY		CR
* this mask is used to guide app_start() execution process. it will enter each mode, but it
  will not execute it until it matches the current mask stored in traffic_status_mask which is
  being written after each mode execution depending on the logical flow of traffic lights
  and pedestrian button being pushed or not.
*/
#define MODE_1_MASK 0b01000001 //65
#define MODE_2_MASK 0b10000010
#define MODE_3_MASK 0b00010100
#define MODE_4_MASK 0b00101000
volatile uint8_t traffic_status_mask;

/* Flags used to handle interrupts in the code*/
volatile uint8_t pedstrain_press_flag;
volatile uint8_t pedstrain_mode_flag;
volatile uint8_t in_delay_flag;

void app_init();
void app_start();
void traffic_mode_1_CR_PG();
void traffic_mode_2_CRY_PGY();
void traffic_mode_3_CG_PR();
void traffic_mode_4_CGY_PRY();
void turn_off_all_leds();

#endif