#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

void setupDAC()
{
	*CMU_HFPERCLKEN0 |= 0x1 << 17;
	*DAC0_CTRL = 0x50010;
	*DAC0_CH0CTRL = 0x1;
	*DAC0_CH1CTRL = 0x1;
	*DAC0_CH0DATA = 0;
	*DAC0_CH1DATA = 0;
}

void disableDAC()
{
	*DAC0_CH0CTRL = 0;
	*DAC0_CH1CTRL = 0;
	*DAC0_CH0CTRL = 0;
	*DAC0_CH1CTRL = 0;
	*CMU_HFPERCLKEN0 &= ~(1 << 17);
}
