#include "exti.h"
void exti_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;      //结构体定义GPIO_InitTypeDef
	//时钟设置
	EXTI_InitTypeDef  EXTI_InitStructure;//外部中断初始化    初始化外设EXTI寄存器
	NVIC_InitTypeDef NVIC_InitStructure;
	SystemInit();   //打开系统时钟，才能使STM32正常工作


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	  //打开管脚复用功能 才能使用该管脚的外部中断功能

	//GPIO管脚设置
	GPIO_InitStructure.GPIO_Pin = k_left;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;

	GPIO_Init(GPIOE,&GPIO_InitStructure);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);//选择GPIO管脚用作外部中断线路
	//此处一定要记住给端口管脚加上中断外部线路
	/* 设置外部中断的模式 */ 
	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	   //设置使能或失能线路
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;  //设置模式
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;	//设置边沿触发中断请求
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;	//定义选中线路的新状态
	EXTI_Init(&EXTI_InitStructure);

	/* 设置NVIC参数 */	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);		 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn; 	//打开EXTI2的全局中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  //响应优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		  //使能
	NVIC_Init(&NVIC_InitStructure); 

}



