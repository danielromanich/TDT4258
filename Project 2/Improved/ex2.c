#include <stdint.h>
#include <stdbool.h>
#include "efm32gg.h"

void setupTimer(uint32_t);
void setupDAC();
void setupNVIC();
void initSong();
void setupGPIO();

int main(void)
{
    setupGPIO();
	setupDAC();
	//Setting up our interrupts
    setupNVIC();
	//Clearing our interrupt vect
    clearInterrupts();
    *SCR = 0b0101;	//Enable deep sleep
    initSong();
    //chooseSong(&GOT, 0x71f);

	__asm("wfi");		//Go into deep sleep
	return 0;
}

void setupNVIC()
{
	*GPIO_EXTIPSELL = 0x22222222;
	*GPIO_EXTIFALL = 0xFF;
	*GPIO_EXTIRISE = 0xFF;
	*GPIO_IEN = 0xFF;
	*ISER0 |= 0x1802;
}