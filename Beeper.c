
#include "utils.h"
#include "Beeper.h"

#define BEEPER_PIN 6

void InitBeeper( void ){
	//uint32_t pulseWidth_uS = 200; //should at least 10uS
	//uint32_t pulseDelay_uS = 500000;
	
	float dutyCycle = 0.5;
	
	//enable clock on port B
	SET_BITS(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN);
	
	//set mode to alternate function
	FORCE_BITS(GPIOB->MODER, 3UL << (2*BEEPER_PIN), 2UL << (2*BEEPER_PIN));

	//set alternate function to AF 2
	FORCE_BITS(GPIOB->AFR[0], 0xF << (4 * BEEPER_PIN), 2UL << (4 * BEEPER_PIN));
	
	//no pull up, no pull down
	FORCE_BITS(GPIOB->PUPDR, 3UL << (2*BEEPER_PIN), 0);
	
	//enable timer 4 clock
	SET_BITS(RCC->APB1ENR1, RCC_APB1ENR1_TIM4EN);
	
	//up counting
	CLR_BITS(TIM4-> CR1, TIM_CR1_DIR);
	
	//prescaler
	//TIM4->PSC = prescaleValue; --> 1kHz clock is 1ms
	TIM4->PSC = 80000-1;
	
	//auto reload
	TIM4->ARR = 5000 - 1; //auto reload every 500 ms 
	
	//clear ch 1 output cmp registers
	CLR_BITS(TIM4->CCMR1, TIM_CCMR1_OC1M);
	
	//Set the duty cycle
	TIM4 -> CCR1 = dutyCycle * (TIM4->ARR + 1);
	//TIM4 -> CCR1 = 500;
	
	//main output enable
	SET_BITS(TIM4->BDTR, TIM_BDTR_MOE);

	//pwm mode
	SET_BITS(TIM4->CCMR1, TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);
	
	//output polarity active high
	CLR_BITS(TIM4 -> CCER, TIM_CCER_CC1P);
	
	//enable CH1
	SET_BITS(TIM4 -> CCER, TIM_CCER_CC1E);
	
	//enable counter
	SET_BITS(TIM4->CR1, TIM_CR1_CEN);

}

void Beeper_SetFrequency( uint32_t hertz ){
	uint32_t periodInMillis = (1.0 / (double)hertz) * 1000;
	uint32_t autoReloadValue = periodInMillis * 10 -1;
	
	TIM4->ARR = autoReloadValue;
	TIM4 -> CCR1 = 0.5 * (TIM4->ARR + 1);
}

