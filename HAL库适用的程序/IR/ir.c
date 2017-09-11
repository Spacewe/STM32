#include "ir.h"
uint32_t hw_jsm;	
uint8_t  hw_jsbz; 


uint8_t HW_jssj()
{
	uint8_t t=0;
	while(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_15)==GPIO_PIN_SET)//¸ßµçÆ½
	{
		t++;
		//HAL_Delay(20/1000);
		delay_us(20);

		if(t>=250) return t;
	}

	return t;
}
void delay_us(uint32_t i)
{
	uint32_t temp;
	SysTick->LOAD=9*i;		 //ÉèÖÃÖØ×°ÊýÖµ, 72MHZÊ±
	SysTick->CTRL=0X01;		 //Ê¹ÄÜ£¬¼õµ½ÁãÊÇÎÞ¶¯×÷£¬²ÉÓÃÍâ²¿Ê±ÖÓÔ´
	SysTick->VAL=0;		   	 //ÇåÁã¼ÆÊýÆ÷
	do
	{
		temp=SysTick->CTRL;		   //¶ÁÈ¡µ±Ç°µ¹¼ÆÊýÖµ
	}
	while((temp&0x01)&&(!(temp&(1<<16))));	 //µÈ´ýÊ±¼äµ½´ï
	SysTick->CTRL=0;	//¹Ø±Õ¼ÆÊýÆ÷
	SysTick->VAL=0;		//Çå¿Õ¼ÆÊýÆ÷
}
