#ifndef	_key_H
#define _key_H
#include "stm32f10x.h"
#define K_UP GPIO_Pin_0
#define K_DOWN GPIO_Pin_3
#define K_RIGHT GPIO_Pin_4
#define K_LEFT GPIO_Pin_2

#define k_up GPIO_ReadInputDataBit(GPIOA,K_UP)		 //获取按键的状态
#define k_down GPIO_ReadInputDataBit(GPIOE,K_DOWN)
#define k_right GPIO_ReadInputDataBit(GPIOE,K_RIGHT)	   //不能加 ;
#define k_left GPIO_ReadInputDataBit(GPIOE,K_LEFT)
		
void key_init(void);
void key_break(void);		


#endif
