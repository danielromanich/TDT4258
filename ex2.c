#include <stdint.h>
#include <stdbool.h>
#include "efm32gg.h"

void setupTimer(uint32_t);
void setupDAC();
void setupNVIC();

void setupGPIO();
void startPolling();

/*
 * Your code will start executing here 
 */
int main(void)
{
	/*
	 * Call the peripheral setup functions 
	 */
	setupGPIO();
	setupDAC();
	//setupTimer(SAMPLE_PERIOD); Not setting up timer because we want to deep sleep until we generate sounds

	startPolling();
	
	
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
