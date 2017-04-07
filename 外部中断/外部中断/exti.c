#include "exti.h"
void exti_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;      //�ṹ�嶨��GPIO_InitTypeDef
	//ʱ������
	EXTI_InitTypeDef  EXTI_InitStructure;//�ⲿ�жϳ�ʼ��    ��ʼ������EXTI�Ĵ���
	NVIC_InitTypeDef NVIC_InitStructure;
	SystemInit();   //��ϵͳʱ�ӣ�����ʹSTM32��������


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	  //�򿪹ܽŸ��ù��� ����ʹ�øùܽŵ��ⲿ�жϹ���

	//GPIO�ܽ�����
	GPIO_InitStructure.GPIO_Pin = k_left;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;

	GPIO_Init(GPIOE,&GPIO_InitStructure);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);//ѡ��GPIO�ܽ������ⲿ�ж���·
	//�˴�һ��Ҫ��ס���˿ڹܽż����ж��ⲿ��·
	/* �����ⲿ�жϵ�ģʽ */ 
	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	   //����ʹ�ܻ�ʧ����·
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;  //����ģʽ
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;	//���ñ��ش����ж�����
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;	//����ѡ����·����״̬
	EXTI_Init(&EXTI_InitStructure);

	/* ����NVIC���� */	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);		 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn; 	//��EXTI2��ȫ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  //��Ӧ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		  //ʹ��
	NVIC_Init(&NVIC_InitStructure); 

}



