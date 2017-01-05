/*
(C)2017 Richard Kuroshio
基于宋雪松《手把手教你学51单片机》
真正实现60进制的计时器
*/
#include<reg51.h>
unsigned char code LedChar[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//数码管字符码
unsigned char LedBuff[6]={0x00,0x00,0x00,0x00,0x00,0x00};//显示所需的数码管初始值，防止误动作，全部熄灭。
sbit Latch1=P2^2;//段锁存
sbit Latch2=P2^3;//位锁存
int main()
{ 
	unsigned int count=0;//毫秒计数
	unsigned int second=0;//秒计数
	unsigned int minute=0;//分计数
	unsigned int hour=0;//时计数
	unsigned int LedCode=0;//数码管编号
	TMOD=0x01;//T0 MODE 1
	TH0=0xfc;
	TL0=0x67;//0xFC67 1ms
	TR0=1;
	while(1)
	{
		if(TF0==1)
		{
			TF0=0;
			TH0=0xfc;
			TL0=0x67;
			count++;
			if(count>=1000)
			{
				count=0;
				second++;
				if(second>=60)//其实吧，一分钟=59s（-1s哪去了？献给长者了（大雾））
				{
					second=0;
					minute++;
					if(minute>=60)
					{
						minute=0;
						hour++;
					}
				}
				LedBuff[0]=LedChar[second%10];//从低到高将数字转化为数码管显示字符送到对应数码管上
				LedBuff[1]=LedChar[second/10%10];
				LedBuff[2]=LedChar[minute%10];
				LedBuff[3]=LedChar[minute/10%10];
				LedBuff[4]=LedChar[hour%10];
				LedBuff[5]=LedChar[hour/10%10];
			}
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
					LedCode=0;//一共需要六个数码管，则需要及时清零，不然就全都不亮了= =
					P0=LedBuff[5];
					Latch1=1;
					Latch1=0;
				}
			}
		}
	}