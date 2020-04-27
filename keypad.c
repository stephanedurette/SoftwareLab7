#include "keypad.h"
#include "LED.h"
#include "utils.h"

#define DELAY 				for( uint32_t i = 0; i < DELAY_COUNT; i++)
#define DELAY_COUNT 	10000000UL

uint8_t len = 4;
uint16_t outputs[] = {15, 14, 13, 12};
uint16_t inputs[] = {1, 2, 3, 5};


//Initializes pins used as keyboard columns and rows
void InitKeypad(){
	
	RCC->AHB2ENR |=   RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOEEN;
	
	for(int i = 0; i < len; i++){
		FORCE_BITS(GPIOE -> MODER, 0x03 << (2 * outputs[i]), 0x01 << (2 * outputs[i])); //digital output = 0x01
		FORCE_BITS(GPIOE -> OTYPER, 1 << (2 * outputs[i]), 0x01 << (2 * outputs[i])); //open drain = 0x01
		FORCE_BITS(GPIOE -> OSPEEDR, 0x03 << (2 * outputs[i]), 0x00 << (2 * outputs[i])); //low speed = 0x00
		FORCE_BITS(GPIOE -> PUPDR, 0x03 << (2 * outputs[i]), 0x01 << (2 * outputs[i])); //pull up = 0x01
		
		FORCE_BITS(GPIOA -> MODER, 0x03 << (2 * inputs[i]), 0x00 << (2 * inputs[i])); //input mode = 0x00
		FORCE_BITS(GPIOA -> PUPDR, 0x03 << (2 * inputs[i]), 0x10 << (2 * inputs[i])); //pull up= 0x01
	}

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

	GPIOE -> ODR &= 0x0FFF; //Clear all outputs
	
	for (int j = 0; j < len; j++){
		GPIOE -> ODR |= (1UL << outputs[j]); //Set Current output
	
		for (int i = 0; i < len; i++){
			if (!(GPIOA -> IDR & (1UL << inputs[i]))){
				return (enum Keys)(j * len + i);
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
	
}

