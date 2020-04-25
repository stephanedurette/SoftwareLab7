#ifndef _BEEPER_H
#define _BEEPER_H
#include "stm32l476xx.h"

void InitBeeper( void );
void Beep( uint32_t hertz );

void StopBeep( void );

#endif

