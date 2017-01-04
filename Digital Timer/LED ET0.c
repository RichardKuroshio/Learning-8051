/*
数码管计时器
(C)2017 Richard Kuroshio
基于宋雪松《手把手教你学51单片机》和德飞莱LY-51S开发板实现
不知什么原因计时速度明显加快？不知是否和晶振精度有关
*/
#include<reg51.h>
unsigned char code LedChar[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//数码管字符码
unsigned char LedBuff[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//显示所需的数码管初始值，防止误动作，全部熄灭。不能加code，不然只能读不能修改赋值。
sbit Latch1=P2^2;//段锁存
sbit Latch2=P2^3;//位锁存
unsigned int count=0;//毫秒计数
unsigned int LedCode=0;//数码管编号
//变量在主函数定义有你受的- -b
int main()
{
	unsigned long second=0;//秒计数，long型
	EA=1;//中断使能
	TMOD=0x01;//T0 模式1，16位计数器
	TH0=0xfc;
	TL0=0x67;//0xfc67 1ms
	TR0=1;
	ET0=1;//T0中断使能
	while(1)
	{

		if(count>=1000)//1000ms=1s
		{
			count=0;
			second++;
			LedBuff[0]=LedChar[second%10];//从低到高将数字转化为数码管显示字符送到对应数码管上
			LedBuff[1]=LedChar[second/10%10];
			LedBuff[2]=LedChar[second/100%10];
			LedBuff[3]=LedChar[second/1000%10];
			LedBuff[4]=LedChar[second/10000%10];
			LedBuff[5]=LedChar[second/100000%10];
			LedBuff[6]=LedChar[second/1000000%10];
			LedBuff[7]=LedChar[second/10000000%10];
		}
	}
}
void InterrptTimer0() interrupt 1//T0中断触发
{
	TH0=0xfc;
	TL0=0x67;
	count++;//中断计数，每1ms触发一次
	P0=0x00;//数码管消隐
				if(LedCode==0)
				{
					P0=0x7f;//共阴极数码管，置零点亮
					Latch2=1;
					Latch2=0;
					LedCode++;
					P0=LedBuff[0];
					Latch1=1;
					Latch1=0;
				}
				else if(LedCode==1)//中间一度将else if误写作if，导致运行周期加长，数码管亮度明显不足。
				{
					P0=0xbf;
					Latch2=1;
					Latch2=0;
					LedCode++;
					P0=LedBuff[1];
					Latch1=1;
					Latch1=0;
				}
				else if(LedCode==2)
				{
					P0=0xdf;
					Latch2=1;
					Latch2=0;
					LedCode++;
					P0=LedBuff[2];
					Latch1=1;
					Latch1=0;
				}
				else if(LedCode==3)
				{
					P0=0xef;
					Latch2=1;
					Latch2=0;
					LedCode++;
					P0=LedBuff[3];
					Latch1=1;
					Latch1=0;
				}
				else if(LedCode==4)
				{
					P0=0xf7;
					Latch2=1;
					Latch2=0;
					LedCode++;
					P0=LedBuff[4];
					Latch1=1;
					Latch1=0;
				}
				else if(LedCode==5)
				{
					P0=0xfb;
					Latch2=1;
					Latch2=0;
					LedCode++;
					P0=LedBuff[5];
					Latch1=1;
					Latch1=0;
				}
				else if(LedCode==6)
				{
					P0=0xfd;
					Latch2=1;
					Latch2=0;
					LedCode++;
					P0=LedBuff[6];
					Latch1=1;
					Latch1=0;
				}
				else if(LedCode==7)
				{
					P0=0xfe;
					Latch2=1;
					Latch2=0;
					LedCode=0;
					P0=LedBuff[7];
					Latch1=1;
					Latch1=0;
				}
}