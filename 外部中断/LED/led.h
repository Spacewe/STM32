#ifndef	_LED_H
#define _LED_H
#include "stm32f10x.h"
#define LED  GPIO_Pin_All
		
		
void LED_Init(void);	//LED��ʼ������
void led_display(void);

#endif

