#include "key.h"
#include "systick.h"
#include "smg.h"
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

void key_break()
{

}


