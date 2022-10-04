#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "../../Utilities/typedefs.h"
#include <avr/interrupt.h>

/* initialize global interrupt setting  sei()*/
void global_interrupt_init();


/* define sensing mode for external interrupt*/
typedef enum INT_sense_mode {rising_edge, falling_edge, logic_change, low_level } INT_sense_mode;
void external_interrupt_sense_mode(uint8_t interrupt_num,  INT_sense_mode mode);


/* initialize specific external interrupt*/
void external_interrupt_init(uint8_t interrupt_num);

#endif