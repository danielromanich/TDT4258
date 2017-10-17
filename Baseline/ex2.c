#include <stdint.h>
#include <stdbool.h>
#include "efm32gg.h"

void setupTimer(uint32_t);
void setupDAC();
void setupNVIC();
void initSong();

void setupGPIO();
void startPolling();

int main(void)
{
	/*
	 * Call the peripheral setup functions 
	 */
	setupGPIO();
	setupDAC();
	initSong();
	*SCR = 0b0101;	//Enable deep sleep

	//Starting the method that is polling our buttons
    startPolling();

	return 0;
}