#ifndef _BEEPER_H
#define _BEEPER_H
#include "stm32l476xx.h"

void InitBeeper( void );
void Beeper_SetFrequency( uint32_t hertz );


#endif

