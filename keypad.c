#include "keypad.h"

//Initializes pins used as keyboard columns and rows
void InitKeypad(){
	
		/* Enable GPIOs clock */ 	
	RCC->AHB2ENR |=   RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOEEN;
	
	//GPIO init Rows as open drain output with pullups enabled PE12 through PE15
	for(int i = 12; i < 16; i++){
		GPIOE->MODER &= ~(3UL << (2*i)); //clear mode bits
		GPIOE->MODER |= 1UL<<(2*i); //mode 01 = digital output
		
		//set output of pin as open drain
		// 0 = push pull
		// 1 = open drain
		GPIOE->OTYPER |= (1UL<<(2*i));
		
		//set the output speed of the pin a low
		// 00 = low speed
		GPIOE->OSPEEDR &= ~(3U<<(2*i));
	
		//set pins as pull up = 01
		GPIOE->PUPDR &= ~(3UL<<(2*i));
		GPIOE->PUPDR |= (1UL<<(2*i));
		
	}
	
	//Set up input pins for the columns PA1,PA2,PA3 and PA5 as inputs with pull up
	for(uint16_t i = 1; i < 4; i++){	
		GPIOA->MODER &= (~3UL << (2 * i));
	}
	GPIOA->MODER &= (~3UL << (2 * 5));
	
	
	//All columns have pull up
	for(uint16_t i = 1; i < 4; i++){	
		GPIOA->PUPDR |= (2UL << (2 * i));
		GPIOA->PUPDR &= ~(1UL << (2 * i)); 
	}
	GPIOA->PUPDR |= (2UL << (2 * 5));
	GPIOA->PUPDR &= ~(1UL << (2 * 5)); 
	
	
	return;
}

//Scans the Keypad
//Returns what key is pressed in the form of Key enum
enum Keys GetKey( void ){
	
	//Pull each one of the rows low
	for(int i = 12; i < 16; i++){
		GPIOE->MODER |= (1<<(1*i)); //Turn on row
		
		//Check the columns
		for(int j = 1; j < 4; j++){
			if(GPIOA->IDR & (1UL << j)){
				return (enum Keys) (i*COLUMNS) + j;
			}
		}		
		if(GPIOA->IDR & (1UL << 5)){
			return (enum Keys) (i*COLUMNS) + 5;
		}
		
		GPIOE->MODER &= ~(1<<(1*i)); //turn off row
	}
	
	return Key_None;
}


