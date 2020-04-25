#ifndef __KEYPAD_H__
#define __KEYPAD_H__

#include "stm32l476xx.h"

enum Keys {Key_None = -1, Key_1, Key_2, Key_3, Key_4, Key_5, Key_6, Key_7, Key_8, Key_9, Key_0, Key_Pound, Key_Hash, Key_A, Key_B, Key_C, Key_D};

enum Keys GetKey( void );

#endif