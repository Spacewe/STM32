#include "led.h"
void delay(u32 i) //延时函数
{
	while(i--);
}
void LED_Init()		   //LED初始化函数
{
	GPIO_InitTypeDef GPIO_InitStructure;      //结构体定义GPIO_InitTypeDef
	//时钟设置
	SystemInit();   //打开系统时钟，才能使STM32正常工作
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//GPIO管脚设置
	GPIO_InitStructure.GPIO_Pin = LED;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	GPIO_Init(GPIOC,&GPIO_InitStructure);
				
}


void led_display()
{
    GPIO_SetBits(GPIOC, LED);     
	delay(6000000);
	GPIO_ResetBits(GPIOC,LED);
	delay(6000000);
		
}

