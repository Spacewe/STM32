#include "time.h"
void time_init()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	//先定时器清空，防止之前的中断干扰
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);	  //TIM_IT_Update为要清除的中断源
		
	TIM_TimeBaseInitStructure.TIM_Period = 2000; 
	TIM_TimeBaseInitStructure.TIM_Prescaler = 35999; 
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM2, & TIM_TimeBaseInitStructure);
	TIM_Cmd(TIM3,ENABLE);   //定时器使能
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE ); //中断使能
		/* 设置NVIC参数 */	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);		 
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 	//打开TIM3的全局中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  //响应优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		  //使能
	NVIC_Init(&NVIC_InitStructure); 
}

