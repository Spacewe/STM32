#include "led.h"
#include "systick.h"
//void delay(u32 i) //��ʱ����
//{
//	while(i--);
//}
void LED_Init()		   //LED��ʼ������
{
	GPIO_InitTypeDef GPIO_InitStructure;      //�ṹ�嶨��GPIO_InitTypeDef
	//ʱ������
	SystemInit();   //��ϵͳʱ�ӣ�����ʹSTM32��������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//GPIO�ܽ�����
	GPIO_InitStructure.GPIO_Pin = LED;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	GPIO_Init(GPIOC,&GPIO_InitStructure);
				
}


void led_display()
{	
	u32 i=100; 
	while(i--)
	{
	   	GPIO_SetBits(GPIOC, LED);     
		delay_ms(1000);
		GPIO_ResetBits(GPIOC,LED);
		delay_ms(1000);
	
	}
    
		
}

