#include "key.h"
void key_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;      //�ṹ�嶨��GPIO_InitTypeDef
	//ʱ������
	SystemInit();   //��ϵͳʱ�ӣ�����ʹSTM32��������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);
	//GPIO�ܽ�����
	GPIO_InitStructure.GPIO_Pin = K_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;

	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = K_DOWN|K_RIGHT|K_LEFT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;

	GPIO_Init(GPIOE,&GPIO_InitStructure);

	GPIO_ResetBits(GPIOA,K_UP); //ʹK_UP�˿����һ���͵�ƽ 
}
void delay_us(u32 i)
{
	u32 temp;
	SysTick->LOAD=9*i;		 //������װ��ֵ, 72MHZʱ
	SysTick->CTRL=0X01;		 //ʹ�ܣ����������޶����������ⲿʱ��Դ
	SysTick->VAL=0;		   	 //���������
	do
	{
		temp=SysTick->CTRL;		   //��ȡ��ǰ������ֵ
	}
	while((temp&0x01)&&(!(temp&(1<<16))));	 //�ȴ�ʱ�䵽��
	SysTick->CTRL=0;	//�رռ�����
	SysTick->VAL=0;		//��ռ�����
}
void delay_ms(u32 i)
{
	u32 temp;
	SysTick->LOAD=9000*i;	  //������װ��ֵ, 72MHZʱ
	SysTick->CTRL=0X01;		//ʹ�ܣ����������޶����������ⲿʱ��Դ
	SysTick->VAL=0;			//���������
	do
	{
		temp=SysTick->CTRL;	   //��ȡ��ǰ������ֵ
	}
	while((temp&0x01)&&(!(temp&(1<<16))));	//�ȴ�ʱ�䵽��
	SysTick->CTRL=0;	//�رռ�����
	SysTick->VAL=0;		//��ռ�����
}


