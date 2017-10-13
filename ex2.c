#include <stdint.h>
#include <stdbool.h>
//#include "sound.h"
#include "efm32gg.h"
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
	//chooseSong(&ONEUP, 0x71f);

	//-----------------------------------------------------------------------------------------------
	bool pressed = 1;
	while(1){
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
			pressed = 0;
			break;
		}

		if(pressed){
			playSongBW();
		}
	}
	//-----------------------------------------------------------------------------------------------


	__asm("wfi");		//Go into deep sleep
	/*
	 * TODO for higher energy efficiency, sleep while waiting for
	 * interrupts instead of infinite loop for busy-waiting 
	 */

	return 0;
}

void setupNVIC()
{
	*GPIO_EXTIPSELL = 0x22222222;
	*GPIO_EXTIFALL = 0xFF;
	*GPIO_EXTIRISE = 0xFF;
	*GPIO_IEN = 0xFF;
	*ISER0 |= 0x1802;
	/*
	 * TODO use the NVIC ISERx registers to enable handling of
	 * interrupt(s) remember two things are necessary for interrupt
	 * handling: - the peripheral must generate an interrupt signal - the
	 * NVIC must be configured to make the CPU handle the signal You will
	 * need TIMER1, GPIO odd and GPIO even interrupt handling for this
	 * assignment. 
	 */
}

/*
 * if other interrupt handlers are needed, use the following names:
 * NMI_Handler HardFault_Handler MemManage_Handler BusFault_Handler
 * UsageFault_Handler Reserved7_Handler Reserved8_Handler
 * Reserved9_Handler Reserved10_Handler SVC_Handler DebugMon_Handler
 * Reserved13_Handler PendSV_Handler SysTick_Handler DMA_IRQHandler
 * GPIO_EVEN_IRQHandler TIMER0_IRQHandler USART0_RX_IRQHandler
 * USART0_TX_IRQHandler USB_IRQHandler ACMP0_IRQHandler ADC0_IRQHandler
 * DAC0_IRQHandler I2C0_IRQHandler I2C1_IRQHandler GPIO_ODD_IRQHandler
 * TIMER1_IRQHandler TIMER2_IRQHandler TIMER3_IRQHandler
 * USART1_RX_IRQHandler USART1_TX_IRQHandler LESENSE_IRQHandler
 * USART2_RX_IRQHandler USART2_TX_IRQHandler UART0_RX_IRQHandler
 * UART0_TX_IRQHandler UART1_RX_IRQHandler UART1_TX_IRQHandler
 * LEUART0_IRQHandler LEUART1_IRQHandler LETIMER0_IRQHandler
 * PCNT0_IRQHandler PCNT1_IRQHandler PCNT2_IRQHandler RTC_IRQHandler
 * BURTC_IRQHandler CMU_IRQHandler VCMP_IRQHandler LCD_IRQHandler
 * MSC_IRQHandler AES_IRQHandler EBI_IRQHandler EMU_IRQHandler 
 */
