#include "beep.h"

void BEEP_Init()		   //BEEP��ʼ������
{
	GPIO_InitTypeDef          GPIO_InitStructure;      //�ṹ�嶨��GPIO_InitTypeDef
	//ʱ������
	SystemInit();   //��ϵͳʱ�ӣ�����ʹSTM32��������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//GPIO�ܽ�����
	GPIO_InitStructure.GPIO_Pin = BUZ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	GPIO_Init(GPIOB,&GPIO_InitStructure);

	
}


void delay(u32 i) //��ʱ����
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





