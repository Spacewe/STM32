#include "smg.h"
#include "systick.h"
u8 smgduan[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0X07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
void smg_init()
{
   	GPIO_InitTypeDef GPIO_InitStructure;      //结构体定义GPIO_InitTypeDef
	//时钟设置
	SystemInit();   //打开系统时钟，才能使STM32正常工作
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//GPIO管脚设置
	GPIO_InitStructure.GPIO_Pin = smg_duan;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	GPIO_Init(GPIOC,&GPIO_InitStructure);
}
void static_smg_display()
{
	  u8 i;
	  for(i=0;i<16;i++)
	  {
	  	GPIO_Write(GPIOC,(u16)~(smgduan[i]));
	  	delay_ms(1000);
	  }
}



