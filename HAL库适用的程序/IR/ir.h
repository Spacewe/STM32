#ifndef _hwjs_H
#define _hwjs_H
#include "stm32f1xx_hal.h"

//void hwjs_init(void);
uint8_t HW_jssj(void);
void delay_us(uint32_t i);

extern uint32_t hw_jsm;
extern uint8_t  hw_jsbz;



#endif
