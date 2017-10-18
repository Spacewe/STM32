# STM32
使用代码时需要在keil中进行一些修改
1. 要将在APP文件夹中创建的.c文件添加到工程中的APP下
2. 每个.c和.h文件最后一行后还要至少一个空行
3. 要将在APP文件夹中创建的文件夹（比如systick)添加到Include Paths中
4. 如果要在stdperiph_Drive中使用其他库文件（比如定时器中的stm32f10x_tim.c）,也要将其添加到stdperiph_Drive下







##  STM32CubeMx

注释为STM32CubeMx的都是用STM32CubeMx和keil5实现的相关功能，目录下为STM32CubeMx工程，点击.ioc文件即可运行；keil工程为压缩包格式。



###### USART实现不定长接收

[使用DMA+空闲中断方式](https://github.com/Spacewe/STM32/tree/master/USART%E4%B8%8D%E5%AE%9A%E9%95%BF%E6%8E%A5%E6%94%B6%EF%BC%88DMA%2B%E7%A9%BA%E9%97%B2%E4%B8%AD%E6%96%AD%EF%BC%89)
