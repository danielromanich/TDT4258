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

int main(void)
{
	/*
	 * Call the peripheral setup functions 
	 */
	setupGPIO();
	setupDAC();

	*SCR = 0b0101;	//Enable deep sleep

	//Since we are polling we need to keep checking the button to see if something was pressed.
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
		case BUTTON3:
		case BUTTON4:
		case BUTTON5:
		case BUTTON6:
		case BUTTON7:
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
	return 0;
}