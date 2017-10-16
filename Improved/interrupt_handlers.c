#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "sound.h"

#define BUTTON1 0
#define BUTTON2 1
#define BUTTON3 2
#define BUTTON4 3
#define BUTTON5 4
#define BUTTON6 5
#define BUTTON7 6
#define BUTTON8 7

void clearInterrupts();

int buttonCount = 8;

void onButtonPushed();
int getState(int input);
//void disableInterrupts();


/*
 * TIMER1 interrupt handler 
 */
void __attribute__ ((interrupt)) TIMER1_IRQHandler()
{
	clearInterrupts();

	//Do checks
	if (progress > currentNoteLen) {
		songProgress++;
		progress = 0;
	} else {
		progress++;
	};

	if (songProgress > currentSong->size) {
		stopSong();
		return;
	}
	//Set volume
	Note* n = currentSong->notes[songProgress];
	int offset = (i % n->noteCount);
	setNote(n, offset);
	//setNote(currentSong.notes[songProgress], songProgress);
	//Do updates
	i++;
}

/*
 * GPIO even pin interrupt handler 
 */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler()
{
	clearInterrupts();
	onButtonPushed();
}

/*
 * GPIO odd pin interrupt handler 
 */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()
{
	clearInterrupts();
	onButtonPushed();
}

void onButtonPushed()
{
	uint32_t value = (*GPIO_PC_DIN ^ 0xFFFFFFFF) & 0xFF;
	switch (getState(value)) {
		/*
		 * BUTTONS 1-8 has been defined. To enable another button make a new case. 
		 */
	case BUTTON1:
		chooseSong(&THATSNOMOON, 0x3FFF);
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
		break;
	}
}

void clearInterrupts()
{
	*GPIO_IFC = *GPIO_IF;
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