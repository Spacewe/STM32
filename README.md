# STM32
使用代码时需要在keil中进行一些修改
1. 要将在APP文件夹中创建的.c文件添加到工程中的APP下
2. 每个.c和.h文件最后一行后还要至少一个空行
3. 要将在APP文件夹中创建的文件夹（比如systick)添加到Include Paths中
4. 如果要在stdperiph_Drive中使用其他库文件（比如定时器中的stm32f10x_tim.c）,也要将其添加到stdperiph_Drive下







##  STM32CubeMx

注释为STM32CubeMx的都是用STM32CubeMx和keil5实现的相关功能，目录下为STM32CubeMx工程，点击.ioc文件即可运行；keil工程为压缩包格式。

