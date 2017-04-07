#include "key.h"
#include "systick.h"
#include "smg.h"
void key_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;      //结构体定义GPIO_InitTypeDef
	//时钟设置
	SystemInit();   //打开系统时钟，才能使STM32正常工作
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);
	//GPIO管脚设置
	GPIO_InitStructure.GPIO_Pin = K_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;

	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = K_DOWN|K_RIGHT|K_LEFT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;

	GPIO_Init(GPIOE,&GPIO_InitStructure);

	GPIO_ResetBits(GPIOA,K_UP); //使K_UP端口输出一个低电平 
}

void key_break()
{

}


