#ifndef _BEEP_H
#define _BEEP_H
#include "stm32f10x.h"
#define BUZ GPIO_Pin_5
void delay(u32 i);
void BEEP_Init(void);
void beep_display(void);


#endif
