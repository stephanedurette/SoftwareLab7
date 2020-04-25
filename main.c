//-------------------------------------------------------------------
// Hack demo to toggle red and green LEDS on Discovery board
// Jan 2019 - WPS
//
// Uses Zhu's SysClock code to init system clocks
//-------------------------------------------------------------------

#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "lcd.h"

// delay count between changing LED states
#define DELAY_COUNT 10000000UL
#define DELAY for( uint32_t i = 0; i < DELAY_COUNT; i++)
#define FOREVER for(;;)

int main(void){
	System_Clock_Init(); 	// Switch System Clock = 80 MHz
	LED_Init();						// Init GPIO bits to drive LEDs
	LCDinit();
	
	FOREVER {
		LCDclear();
		Green_LED_Toggle();
		DELAY;	
	}
	
} 

