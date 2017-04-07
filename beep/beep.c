#include "beep.h"

void BEEP_Init()		   //BEEP初始化函数
{
	GPIO_InitTypeDef          GPIO_InitStructure;      //结构体定义GPIO_InitTypeDef
	//时钟设置
	SystemInit();   //打开系统时钟，才能使STM32正常工作
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//GPIO管脚设置
	GPIO_InitStructure.GPIO_Pin = BUZ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	GPIO_Init(GPIOB,&GPIO_InitStructure);

	
}


void delay(u32 i) //延时函数
{
	while(i--);
}

void beep_display()
{
	u32 i=1000;
	while(i--)
	{
	    GPIO_SetBits(GPIOB, BUZ);     
		delay(i);
		GPIO_ResetBits(GPIOB,BUZ);
		delay(i--);
	}
    

}





