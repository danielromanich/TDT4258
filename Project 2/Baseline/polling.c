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

int buttonCount = 8;

int getState(int input);
void playSongBW();

void startPolling()
{
	while(1) {
		bool pressed = 1;
		uint32_t value = ~(*GPIO_PC_DIN) & 0xFF;
		switch (getState(value)) {
				/*
				 * BUTTONS 1-8 has been defined. To enable another button make a new case. 
				 */
            case BUTTON1:
                chooseSong(&GOT, 0x3400);
                break;
            case BUTTON2:
                chooseSong(&SHOOTING, 0x3300);
                break;
            case BUTTON3:
                chooseSong(&OUT, 0x3500);
                break;
            case BUTTON4:
                chooseSong(&PING, 0x3500);
                break;
            case BUTTON5:
                chooseSong(&PONG, 0x3500);
                break;
            case BUTTON6:
                chooseSong(&WALL, 0x3500);
            case BUTTON7:
			case BUTTON8:
				break; //Unused buttons
			default:
				pressed = 0;
				break;
		}

		if(pressed){
			playSongBW();
		}
	}
}

int getState(int input)
{
	for (int i = 0; i < buttonCount; i++) {
		if (((input >> i) & 0x1) == 1) {
			return i;
		}
	}
	return -1;
}
