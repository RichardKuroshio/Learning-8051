关于在使用开发板时的一些问题。
==================
这个计时器项目中用到了多个数码管，而在《手》一书使用的KST-51和我实际用的LY-51S的定义和使用方法是不同的，在这里需要说明一下。
##硬件连接
LY-51S采用的是使用两个74HC5730缓冲器实现数码管的位选和段选，并使用了2个LG3641共阴数码管。   
KST-51则使用了6个独立的共阳数码管。74HC138译码器进行位选，74HC245缓冲器段选。   
![LY-51S](https://github.com/RichardKuroshio/Learning-8051/blob/master/Screenshots/a.jpg)
![KST-51](https://github.com/RichardKuroshio/Learning-8051/blob/master/Screenshots/b.jpg)   
图片仅作示意，并不代表真实电路连接。
##程序
《手》一书中提到的LedfBuff初始定义值是这样的
    unsigned char LedBuff[6]={0xff,0xff,0xff,0xff,0xff,0xff};
因为要使用共阴数码管，就只能将其改成0x00；
《手》一书还提到了数码管的消隐问题，这个在LY的视频中一开始就提到了。在向P0口发送段编码或位编码后，就完成一次锁存。
    Latchx=1;
    Latchx=0;//x是1或者2，对应着段锁存或者位锁存。
不知是什么原因，采用了中断函数的计数器在定时器置位等参数全部不变的情况下计时速度加快。
