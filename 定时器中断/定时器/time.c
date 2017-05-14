#include "time.h"
void time_init()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	//�ȶ�ʱ����գ���ֹ֮ǰ���жϸ���
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);	  //TIM_IT_UpdateΪҪ������ж�Դ
		
	TIM_TimeBaseInitStructure.TIM_Period = 2000; 
	TIM_TimeBaseInitStructure.TIM_Prescaler = 35999; 
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM2, & TIM_TimeBaseInitStructure);
	TIM_Cmd(TIM3,ENABLE);   //��ʱ��ʹ��
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE ); //�ж�ʹ��
		/* ����NVIC���� */	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);		 
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 	//��TIM3��ȫ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  //��Ӧ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		  //ʹ��
	NVIC_Init(&NVIC_InitStructure); 
}

