#ifndef TIMER_H_
#define TIMER_H_

#include "../../Utilities/typedefs.h"
#include "../../Utilities/registers.h"
#include <avr/io.h>
#include <math.h>
#define FCPU 1000000



/*enums used to define the timer used and its configurations*/
typedef enum EN_timer_num{timer_0,timer_1,timer_2}EN_timer_num;
typedef enum EN_timer_mode{normal,CTC,PWM_phase_correct,fast_PWM}EN_timer_mode;
typedef enum EN_timer_prescaler{automatic,pre_1,pre_8,pre_64,pre_256,pre_1024}EN_timer_prescaler;
typedef enum EN_timer_interrupt{enable,disable}EN_timer_interrupt;
typedef enum EN_delay_unit{seconds,millis,micros}EN_delay_unit;
	
typedef struct ST_delay{
double init_value;
double n_overflow;
uint16_t prescaler_value;
double n_overflow_flag;//must be reset manually after each delay use
}ST_delay;



	
/*initialization timer*/


void timer_init(EN_timer_num timer_num, EN_timer_prescaler prescaler, double delay_value, EN_delay_unit delay_unit);

void blocking_delay_0();


#endif