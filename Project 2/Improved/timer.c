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
	*TIMER1_TOP = period;
	*TIMER1_IEN = 0x1;
	*ISER0 |= 0x1 << 12;
	*TIMER1_CMD = 0x1;
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
