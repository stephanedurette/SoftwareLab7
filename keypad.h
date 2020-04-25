#ifndef __KEYPAD_H__
#define __KEYPAD_H__

#include "stm32l476xx.h"

#define ROWS 4
#define COLUMNS 4 

enum Keys {Key_None = -1, Key_1, Key_2, Key_3, Key_A, Key_4, Key_5, Key_6,Key_B, Key_7, Key_8, Key_9, Key_C, Key_Pound, Key_0, Key_Hash, Key_D};

//Scans the Keypad
//Returns what key is pressed in the form of Key enum
enum Keys GetKey( void );
void InitKeypad( void );




#endif


