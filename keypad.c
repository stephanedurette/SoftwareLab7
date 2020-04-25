#include "keypad.h"
#include "LED.h"
#include "utils.h"

uint8_t len = 4;
uint32_t outputs[] = {12, 13, 14, 15};
uint32_t inputs[] = {1, 2, 3, 5};

//Initializes pins used as keyboard columns and rows
void InitKeypad(){
	
	RCC->AHB2ENR |=   RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOEEN;
	
	for(uint8_t i = 0; i < len; i++){
		FORCE_BITS(GPIOE -> MODER, 3UL << (2 * outputs[i]), 1UL << (2 * outputs[i])); //digital output = 01
		FORCE_BITS(GPIOE -> OTYPER, 1UL << (outputs[i]), 1UL << (outputs[i])); //open drain = 1, push pull = 0
		FORCE_BITS(GPIOE -> OSPEEDR, 3UL << (2 * outputs[i]), 0 << (2 * outputs[i])); //low speed = 00
		FORCE_BITS(GPIOE -> PUPDR, 3UL << (2 * outputs[i]), 1UL << (2 * outputs[i])); //pull up = 01
		
		FORCE_BITS(GPIOA -> MODER, 3UL << (2 * inputs[i]), 0 << (2 * inputs[i])); //input mode = 00
		FORCE_BITS(GPIOA -> PUPDR, 3UL << (2 * inputs[i]), 1UL << (2 * inputs[i])); //pull up= 01
	}
	/*
		// Enable GPIOs clock // 	
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
	*/
}


//Scans the Keypad
//Returns what key is pressed in the form of Key enum
enum Keys GetKey( void ){
	GPIOE -> ODR &= ~(0xF << outputs[0]); //Clear all outputs
	
	for (int j = 0; j < len; j++){
		GPIOE -> ODR |= (1UL << outputs[j]); //Set Current output
	
		for (int i = 0; i < len; i++){
			if (!(GPIOA -> IDR & (1UL << inputs[i]))){
				//return (enum Keys)(j * len + i);
			}
		}
		volatile uint8_t Idr1 = (GPIOA -> IDR & 1UL << 1) >> 1;
		volatile uint8_t Idr2 = (GPIOA -> IDR & 1UL << 2) >> 2;
		volatile uint8_t Idr3 = (GPIOA -> IDR & 1UL << 3) >> 3;
		volatile uint8_t Idr5 = (GPIOA -> IDR & 1UL << 5) >> 5;
		volatile uint16_t Odr = (GPIOE -> ODR >> 12) & 0xF;
		//int keyPressed = (!(GPIOA -> IDR & (1UL << inputs[i])));
		
		GPIOE -> ODR &= ~(1UL << outputs[j]); //Set Current output
	}
	return Key_None;
	
	/*
	////2
	//uint8_t len = 4;
  //uint16_t outputs[] = {12, 13, 14, 15};
  //uint16_t inputs[] = {1, 2, 3, 5};
	for(int i = 0; i < len; i++){
		GPIOE -> MODER |= 1 << outputs[i];
		
		for(int j = 0; j < len; j++){
			if (GPIOA -> IDR & (1UL << inputs[j])){
				return (enum Keys)(i * len + j);
			}
		}
		
		GPIOE -> MODER &= ~(1 << outputs[i]);
	}
	return Key_None;
	
	
	///3
	//Pull each one of the rows low
	for(int i = 12; i < 16; i++){
		GPIOE->MODER |= (1<<(1*i)); //Turn on row
		
		//Check the columns
		for(int j = 1; j < 4; j++){
			if(GPIOA->IDR & (1UL << j)){
				return  ((i-12)*COLUMNS + (j-1));
			}
		}		
		if(GPIOA->IDR & (1UL << 5)){
			return ((i-12)*COLUMNS + (5-1));
		}
		
		GPIOE->MODER &= ~(1<<(1*i)); //turn off row
	}
	
	return Key_None;
	*/
}
