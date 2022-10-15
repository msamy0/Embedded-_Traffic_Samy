#ifndef TIMER_H_
#define TIMER_H_

#include "../../Utilities/typedefs.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#define FCPU 1000000



typedef enum TIMER_error_handler {TIMER_OK,TIMER_ERROR} TIMER_error_handler;



/*enums used to define the timer used and its configurations*/
typedef enum EN_timer_num{timer_0,timer_1,timer_2}EN_timer_num;
typedef enum EN_timer_mode{normal,CTC,PWM_phase_correct,fast_PWM}EN_timer_mode;
typedef enum EN_timer_prescaler{automatic,pre_1,pre_8,pre_32,pre_64,pre_128,pre_256,pre_1024}EN_timer_prescaler;
typedef enum EN_timer_interrupt{interrupt_enable,interrupt_disable}EN_timer_interrupt;
typedef enum EN_delay_unit{seconds,millis,micros}EN_delay_unit;
	
typedef enum EN_non_blocking_delay_status{stop,start}EN_non_blocking_delay_status;	
	
typedef struct ST_delay{
double init_value;
double n_overflow;
uint16_t prescaler_value;
double n_overflow_flag;//must be reset manually after each delay use
}ST_delay;

volatile uint8_t stop_timer_0_flag;
volatile uint8_t stop_timer_1_flag;
volatile uint8_t stop_timer_2_flag;

volatile ST_delay delay_0;
volatile ST_delay delay_1;
volatile ST_delay delay_2;


	
/*initialization timer*/


TIMER_error_handler timer_init(EN_timer_num timer_num,EN_timer_interrupt timer_interrupt_init, EN_timer_prescaler prescaler, double delay_value, EN_delay_unit delay_unit);

TIMER_error_handler blocking_delay_0();
TIMER_error_handler non_blocking_delay_2(EN_non_blocking_delay_status status);


#endif