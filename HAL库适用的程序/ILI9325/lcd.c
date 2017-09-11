#include "lcd.h"
#include "fsmc.h"
#include "gpio.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STM32F103RBT6,主频72M  单片机工作电压3.3V
//QDtech-TFT液晶驱动 for STM32 IO模拟
//xiao冯@ShenZhen QDtech co.,LTD
//公司网站:www.qdtech.net
//淘宝网站：http://qdtech.taobao.com
//我司提供技术支持，任何技术问题欢迎随时交流学习
//固话(传真) :+86 0755-23594567 
//手机:15989313508（冯工） 
//邮箱:QDtech2008@gmail.com 
//Skype:QDtech2008
//技术交流QQ群:324828016
//创建日期:2013/5/13
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 深圳市全动电子技术有限公司 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////	
/****************************************************************************************************
//=======================================液晶屏数据线接线==========================================//
//DB0       接PD14 
//DB1       接PD15 
//DB2       接PD0 
//DB3       接PD1 
//DB4~DB12  依次接PE7~PE15
//DB13      接PD8 
//DB14      接PD9
//DB15      接PD10  
//=======================================液晶屏控制线接线==========================================//
//LCD_CS	接PG12	//片选信号
//LCD_RS	接PG0	//寄存器/数据选择信号
//LCD_WR	接PD5	//写信号
//LCD_RD	接PD4	//读信号
//LCD_RST	接PC5	//复位信号
//LCD_LED	接PB0	//背光控制信号(高电平点亮)
//=========================================触摸屏触接线=========================================//
//不使用触摸或者模块本身不带触摸，则可不连接
//MO(MISO)	接PF8	//SPI总线输出
//MI(MOSI)	接PF9	//SPI总线输入
//PEN		接PF10	//触摸屏中断信号
//TCS		接PB2	//触摸IC片选
//CLK		接PB1	//SPI总线时钟
**************************************************************************************************/	
	   
//管理LCD重要参数
//默认为竖屏
_lcd_dev lcddev;

//画笔颜色,背景颜色
uint16_t POINT_COLOR = 0x0000,BACK_COLOR = 0xFFFF;  
uint16_t DeviceCode;	 

SRAM_HandleTypeDef hsram2;
//******************************************************************
//函数名：  LCD_WR_REG
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    向液晶屏总线写入写16位指令
//输入参数：Reg:待写入的指令值
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_WR_REG(uint16_t data)
{ 
	LCD->LCD_REG=data;//写入要写的寄存器序号	 	
}

//******************************************************************
//函数名：  LCD_WR_DATA
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    向液晶屏总线写入写16位数据
//输入参数：Data:待写入的数据
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_WR_DATA(uint16_t data)
{
	LCD->LCD_RAM=data;

}
//******************************************************************
//函数名：  LCD_DrawPoint_16Bit
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    写入一个16位数据
//输入参数：(x,y):光标坐标
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_DrawPoint_16Bit(uint16_t color)
{
	LCD_WR_DATA(color); 
	printf("|LCD_DrawPoint_16Bit| %d  %u\n",color,color);
}

//******************************************************************
//函数名：  LCD_WriteReg
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    写寄存器数据
//输入参数：LCD_Reg:寄存器地址
//			LCD_RegValue:要写入的数据
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue)
{	
	LCD->LCD_REG = LCD_Reg;		//写入要写的寄存器序号	 
	LCD->LCD_RAM = LCD_RegValue;//写入数据	     		 
}		   
	 
//******************************************************************
//函数名：  LCD_WriteRAM_Prepare
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    开始写GRAM
//			在给液晶屏传送RGB数据前，应该发送写GRAM指令
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);
}	 

//******************************************************************
//函数名：  LCD_DrawPoint
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    在指定位置写入一个像素点数据
//输入参数：(x,y):光标坐标
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_DrawPoint(uint16_t x,uint16_t y)
{
	LCD_SetCursor(x,y);
	//printf("LCD_DrawPoint %d %d\n",x,y);
	LCD_WR_DATA(POINT_COLOR); 
}

//******************************************************************
//函数名：  LCD_Clear
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    LCD全屏填充清屏函数
//输入参数：Color:要清屏的填充色
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_Clear(uint16_t Color)
{	
	uint32_t index=0; 
	     
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);	

	for(index=0;index<153600;index++)
	{
		LCD->LCD_RAM=Color;		  
	}
} 


//******************************************************************
//函数名：  LCD_GPIOInit
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    液晶屏IO初始化，FSMC总线初始化，液晶初始化前要调用此函数
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//FSMC_NORSRAM_InitTypeDef  FSMC_NORSRAMInitStructure;
  	FSMC_NORSRAM_TimingTypeDef  readWriteTiming; 
	FSMC_NORSRAM_TimingTypeDef  writeTiming;


  hsram2.Instance = FSMC_NORSRAM_DEVICE;
  hsram2.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
	
  __HAL_RCC_FSMC_CLK_ENABLE();//使能FSMC时钟
  	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);	//使能FSMC时钟
		  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOG|RCC_APB2Periph_AFIO,ENABLE);//使能PORTB,D,E,G以及AFIO复用功能时钟

  /*Configure GPIO pin : PC5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PB0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14 
                          |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4 
                          |GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //PB0 推挽输出 背光
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //PC5复液晶屏位
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOC, &GPIO_InitStructure);

 	//PORTD复用推挽输出  
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_14|GPIO_Pin_15;				 //	//PORTD复用推挽输出  
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出   
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOD, &GPIO_InitStructure); 
	  
	//PORTE复用推挽输出  
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //	//PORTD复用推挽输出  
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出   
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOE, &GPIO_InitStructure); 
	  
   	//	//PORTG12复用推挽输出 A0	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_12;	 //	//PORTD复用推挽输出  
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出   
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOG, &GPIO_InitStructure); 
 
	readWriteTiming.AddressSetupTime = 0x01;	 //地址建立时间（ADDSET）为2个HCLK 1/36M=27ns
    readWriteTiming.AddressHoldTime = 0x00;	 //地址保持时间（ADDHLD）模式A未用到	
    readWriteTiming.DataSetupTime = 0x0f;		 // 数据保存时间为16个HCLK,因为液晶驱动IC的读数据的时候，速度不能太快，尤其对1289这个IC。
    readWriteTiming.BusTurnAroundDuration = 0x00;
    readWriteTiming.CLKDivision = 0x00;
    readWriteTiming.DataLatency = 0x00;
    readWriteTiming.AccessMode = FSMC_ACCESS_MODE_A;	 //模式A 
    

	writeTiming.AddressSetupTime = 0x02;	 //0x01 地址建立时间（ADDSET）为1个HCLK  
    writeTiming.AddressHoldTime = 0x00;	 //地址保持时间（A		
    writeTiming.DataSetupTime = 0x05;		 ////0x03 数据保存时间为4个HCLK	
    writeTiming.BusTurnAroundDuration = 0x00;
    writeTiming.CLKDivision = 0x00;
    writeTiming.DataLatency = 0x00;
    writeTiming.AccessMode = FSMC_ACCESS_MODE_A;	 //模式A 

	
    hsram2.Init.NSBank = FSMC_NORSRAM_BANK4;//  这里我们使用NE4 ，也就对应BTCR[6],[7]。
    hsram2.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE; // 不复用数据地址
    hsram2.Init.MemoryType =FSMC_MEMORY_TYPE_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
    hsram2.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;//存储器数据宽度为16bit   
    hsram2.Init.BurstAccessMode =FSMC_BURST_ACCESS_MODE_DISABLE;// FSMC_BurstAccessMode_Disable; 
    hsram2.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
	hsram2.Init.AsynchronousWait=FSMC_ASYNCHRONOUS_WAIT_DISABLE; 
    hsram2.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;   
    hsram2.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;  
    hsram2.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;	//  存储器写使能
    hsram2.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;   
    hsram2.Init.ExtendedMode = FSMC_EXTENDED_MODE_ENABLE; // 读写使用不同的时序
    hsram2.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE; 
    //FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming; //读写时序
    //FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;  //写时序

		  if (HAL_SRAM_Init(&hsram2, &readWriteTiming, &writeTiming) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

//FSMC_NORSRAM_Init();
    //FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //初始化FSMC配置

   	//FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  // 使能BANK1 
			__FSMC_NORSRAM_ENABLE(FSMC_NORSRAM_DEVICE,FSMC_NORSRAM_BANK4);
}
//******************************************************************
//函数名：  LCD_Reset
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    LCD复位函数，液晶初始化前要调用此函数
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_RESET(void)
{
	LCD_RST_CLR;
	HAL_Delay(100);
	//delay_ms(100);	
	LCD_RST_SET;
	HAL_Delay(50);
	//delay_ms(50);
}
 	 
//******************************************************************
//函数名：  LCD_Init
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    LCD初始化
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_Init(void)
{  
     										 
	LCD_GPIOInit();
 	LCD_RESET();

	//************* Start Initial Sequence **********//		
	LCD_WriteReg(0x00E5,0x78F0); 
	LCD_WriteReg(0x0001,0x0100); 
	LCD_WriteReg(0x0002,0x0700); 
	LCD_WriteReg(0x0003,0x1030); 
	LCD_WriteReg(0x0004,0x0000); 
	LCD_WriteReg(0x0008,0x0202);  
	LCD_WriteReg(0x0009,0x0000);
	LCD_WriteReg(0x000A,0x0000); 
	LCD_WriteReg(0x000C,0x0000); 
	LCD_WriteReg(0x000D,0x0000);
	LCD_WriteReg(0x000F,0x0000);
	//power on sequence VGHVGL
	LCD_WriteReg(0x0010,0x0000);   
	LCD_WriteReg(0x0011,0x0007);  
	LCD_WriteReg(0x0012,0x0000);  
	LCD_WriteReg(0x0013,0x0000); 
	LCD_WriteReg(0x0007,0x0000); 
	//vgh 
	LCD_WriteReg(0x0010,0x1690);   
	LCD_WriteReg(0x0011,0x0227);
	//delay_ms(100);
	//vregiout 
	LCD_WriteReg(0x0012,0x009D); //0x001b
	//delay_ms(100); 
	//vom amplitude
	LCD_WriteReg(0x0013,0x1900);
	//delay_ms(100); 
	//vom H
	LCD_WriteReg(0x0029,0x0025); 
	LCD_WriteReg(0x002B,0x000D); 
	//gamma
	LCD_WriteReg(0x0030,0x0007);
	LCD_WriteReg(0x0031,0x0303);
	LCD_WriteReg(0x0032,0x0003);// 0006
	LCD_WriteReg(0x0035,0x0206);
	LCD_WriteReg(0x0036,0x0008);
	LCD_WriteReg(0x0037,0x0406); 
	LCD_WriteReg(0x0038,0x0304);//0200
	LCD_WriteReg(0x0039,0x0007); 
	LCD_WriteReg(0x003C,0x0602);// 0504
	LCD_WriteReg(0x003D,0x0008); 
	//ram
	LCD_WriteReg(0x0050,0x0000); 
	LCD_WriteReg(0x0051,0x00EF);
	LCD_WriteReg(0x0052,0x0000); 
	LCD_WriteReg(0x0053,0x013F);  
	LCD_WriteReg(0x0060,0xA700); 
	LCD_WriteReg(0x0061,0x0001); 
	LCD_WriteReg(0x006A,0x0000); 
	//
	LCD_WriteReg(0x0080,0x0000); 
	LCD_WriteReg(0x0081,0x0000); 
	LCD_WriteReg(0x0082,0x0000); 
	LCD_WriteReg(0x0083,0x0000); 
	LCD_WriteReg(0x0084,0x0000); 
	LCD_WriteReg(0x0085,0x0000); 
	//
	LCD_WriteReg(0x0090,0x0010); 
	LCD_WriteReg(0x0092,0x0600); 
	
	LCD_WriteReg(0x0007,0x0133);
	LCD_WriteReg(0x00,0x0022);//	


	LCD_SetParam();//设置LCD参数	 
	//LCD_LED=1;//点亮背光	 
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	LCD_Clear(WHITE);
}
  		  
/*************************************************
函数名：LCD_SetWindows
功能：设置lcd显示窗口，在此区域写点数据自动换行
入口参数：xy起点和终点
返回值：无
*************************************************/
void LCD_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd)
{	
	if(lcddev.dir==1)//横屏
	{	
	LCD_WR_REG(0x52);	
	LCD_WR_DATA(xStar);
	LCD_WR_REG(0x53);		
	LCD_WR_DATA(xEnd);
	LCD_WR_REG(0x50);	
	LCD_WR_DATA(yStar);
	LCD_WR_REG(0x51);		
	LCD_WR_DATA(yEnd);
	}
	else 
	{
	LCD_WR_REG(0x50);	
	LCD_WR_DATA(xStar);
	LCD_WR_REG(0x51);		
	LCD_WR_DATA(xEnd);
	LCD_WR_REG(0x52);	
	LCD_WR_DATA(yStar);
	LCD_WR_REG(0x53);		
	LCD_WR_DATA(yEnd);
	}
	LCD_WR_REG(lcddev.setxcmd);	
	LCD_WR_DATA(xStar);	
	LCD_WR_REG(lcddev.setycmd);	
	LCD_WR_DATA(yStar);

	LCD_WriteRAM_Prepare();	//开始写入GRAM				
}   

/*************************************************
函数名：LCD_SetCursor
功能：设置光标位置
入口参数：xy坐标
返回值：无
*************************************************/
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{	  	    			
	LCD_WR_REG(lcddev.setxcmd);	
	LCD_WR_DATA(Xpos);
  printf("LCD_SetCursor\n");
	
	LCD_WR_REG(lcddev.setycmd);	
	LCD_WR_DATA(Ypos);
	printf("LCD_SetCursor\n");

	LCD_WriteRAM_Prepare();	//开始写入GRAM	
} 

//设置LCD参数
//方便进行横竖屏模式切换
void LCD_SetParam(void)
{ 	
	lcddev.wramcmd=0x22;
#if USE_HORIZONTAL==1	//使用横屏	  
	lcddev.dir=1;//横屏
	lcddev.width=320;
	lcddev.height=240;
	lcddev.setxcmd=0x21;
	lcddev.setycmd=0x20;			
	LCD_WriteReg(0x03,0x1038);
	LCD_WriteReg(0x0060,0x2700);

#else//竖屏
	lcddev.dir=0;//竖屏				 	 		
	lcddev.width=240;
	lcddev.height=320;
	lcddev.setxcmd=0x20;
	lcddev.setycmd=0x21;	
	LCD_WriteReg(0x03,0x1030);
	LCD_WriteReg(0x0060,0xA700);
#endif
}	  
  


