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
#include "Beeper.h"
#include "Notes.h"

#define DELAY_COUNT 	10000000UL
#define DELAY 				for( uint32_t i = 0; i < DELAY_COUNT; i++)
#define FOREVER 			for(;;)


int toneFrequencies[16] = {C3, D3, E3, F3, G3, A3, B3, C4, D4, E4, F4, G4, A4, B4, C5, D5};


int main(void){
	System_Clock_Init(); 	// Switch System Clock = 80 MHz
	//LED_Init();						// Init GPIO bits to drive LEDs
	LCDinit();
	InitBeeper();
	Beep(C4);
	
	FOREVER {
		DELAY;	
	}
	
} 

