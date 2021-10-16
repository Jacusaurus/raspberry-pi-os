#include "utils.h"
#include "printf.h"
#include "peripherals/timer.h"

const unsigned int interval = 200000;
unsigned int curVal = 0;

void timer_init ( void )
{
	// sets value of TIMER_CTRL, enables timer and interrupt
	put32(TIMER_CTRL, ((1 << 28) | interval));
}

void handle_timer_irq( void ) 
{
	printf("Local timer interrupt received\n\r");
	put32(TIMER_FLAG, (3 << 30));	// clears interrupt flag and reloads the timer
}
