#include <stdint.h>
#include <stdbool.h>
#include "sound.h"
#include "efm32gg.h"


#define BUTTON1 0
#define BUTTON2 1
#define BUTTON3 2
#define BUTTON4 3
#define BUTTON5 4
#define BUTTON6 5
#define BUTTON7 6
#define BUTTON8 7

/*
 * TODO calculate the appropriate sample period for the sound wave(s) you 
 * want to generate. The core clock (which the timer clock is derived
 * from) runs at 14 MHz by default. Also remember that the timer counter
 * registers are 16 bits. 
 */
/*

/*
 * Declaration of peripheral setup functions 
 */
void setupTimer(uint32_t);
void setupDAC();
void setupNVIC();

void setupGPIO();
void playSongBW();

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

	/*
	 * Enable interrupt handling 
	 */
	clearInterrupts();
	//setupNVIC();

	*SCR = 0b0101;	//Enable deep sleep

	//-----------------------------------------------------------------------------------------------
	while(1){
	    bool pressed = 1;
		uint32_t value = (*GPIO_PC_DIN ^ 0xFFFFFFFF) & 0xFF;
		switch (getState(value)) {
			/*
			 * BUTTONS 1-8 has been defined. To enable another button make a new case. 
			 */
		case BUTTON1:
			chooseSong(&GOT, 0x3FFF);
			break;
		case BUTTON2:
			chooseSong(&THATSNOMOON, 0x3FFF);
			break;
		case BUTTON3:
			chooseSong(&THATSNOMOON, 0x3FFF);
			break;
		case BUTTON4:
			chooseSong(&THATSNOMOON, 0x3FFF);
			break;
		case BUTTON5:
			chooseSong(&THATSNOMOON, 0x3FFF);
			break;
		case BUTTON6:
			chooseSong(&THATSNOMOON, 0x3FFF);
			break;
		case BUTTON7:
			chooseSong(&THATSNOMOON, 0x3FFF);
			break;
		case BUTTON8:
			stopSong();
			break;
		default:
			pressed = 0;
			break;
		}

		if(pressed){
			playSongBW();
		}
	}
	//-----------------------------------------------------------------------------------------------


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