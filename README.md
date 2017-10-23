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


###### 使用esp8266实现STM32联网

将STM32与esp8266通过usart2的引脚连接，使用电脑通过STM32配置esp8266,实现与TCP server相互发送数据。
工作流程如下图：
![图像 2.png](http://upload-images.jianshu.io/upload_images/1760243-0d7bc465dd5a2ab9.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
意义：实现了STM32的联网，即STM32的数据可以上传到网上，通过网络也可以控制STM32。

###### STM32实现自动联网
[STM32上电发送指令到esp8266实现配置联网](https://github.com/Spacewe/STM32/tree/master/%E9%80%9A%E8%BF%87STM32%E9%85%8D%E7%BD%AEesp8266%EF%BC%88STM32%E8%87%AA%E5%8A%A8%E5%AE%8C%E6%88%90%EF%BC%89)


### 物联网系统
##### 物联网系统1.0（局域网）
系统组成如下图：
![](http://img.blog.csdn.net/20171021214122882?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvc3VwZXJjZQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

具体介绍见[:](http://blog.csdn.net/superce/article/details/78306724)
