#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

#define CLOCK_FREQUENCY 14000000

/*
 * function to setup the timer 
 */
void setupTimer(uint16_t period)
{
	*CMU_HFPERCLKEN0 |= 0x1 << 6;
	//*TIMER1_TOP = period;
	//*TIMER1_IEN = 0x1;
	//*ISER0 |= 0x1 << 12;
	//*TIMER1_CMD = 0x1;

	/*
	 * TODO enable and set up the timer
	 * 
	 * 1. Enable clock to timer by setting bit 6 in CMU_HFPERCLKEN0 2.
	 * Write the period to register TIMER1_TOP 3. Enable timer interrupt
	 * generation by writing 1 to TIMER1_IEN 4. Start the timer by writing 
	 * 1 to TIMER1_CMD
	 * 
	 * This will cause a timer interrupt to be generated every (period)
	 * cycles. Remember to configure the NVIC as well, otherwise the
	 * interrupt handler will not be invoked. 
	 */
}

void disableTimer()
{
	*TIMER1_IEN = 0;
	*CMU_HFPERCLKEN0 &= (0x1 << 6) ^ 0xFFFFFFFF;
	*TIMER1_CMD = 0;
	*ISER0 &= (0x1 << 12) ^ 0xFFFFFFFF;
	*TIMER1_TOP = 0;
}

void setFrequency(uint16_t frequency)
{
	*TIMER1_TOP = CLOCK_FREQUENCY / frequency;
}
