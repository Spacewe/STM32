#include "smg.h"
#include "systick.h"
#include "key.h"
u8 smgduan[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0X07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
u8 py_smg[]={0xfe,0xfd,0xbf,0xef,0xf7,0xfb,0xbf,0xdf,0xfe};
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
	  u32 j=60;
	  while(j--)
	  {
	  	  

	      u8 i;	// 不能再可执行语句后声明 要在函数最开始声明

		  
		  GPIO_Write(GPIOC,(u16)0x00);
		  delay_ms(300);
		  
		  //delay_ms(3000);
		  for(i=0;i<10;i++)
		  {
		  	GPIO_Write(GPIOC,(u16)~(smgduan[i]));
		  	delay_ms(200);
		  }
		  for(i=9;i!=0;i--)
		  {
		  	GPIO_Write(GPIOC,(u16)~(smgduan[i]));
		  	delay_ms(200);
		  }
		  
	  }
	 
}

void python_smg()
{
	   while(1)
	   {
	   	   u8 k;
		   for(k=0;k<10;k++)
		   {
		   		GPIO_Write(GPIOC,(u16)(py_smg[k]));
			  	delay_ms(245);	
		   }
	   
	   }
	   

}

