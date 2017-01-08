/*
(C)2017 Richard Kuroshio
������ѩ�ɡ��ְ��ֽ���ѧ51��Ƭ����
����ʵ��60���Ƶļ�ʱ��
*/
#include<reg51.h>
unsigned char code LedChar[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//������ַ���
unsigned char LedBuff[6]={0x00,0x00,0x00,0x00,0x00,0x00};//��ʾ���������ܳ�ʼֵ����ֹ������ȫ��Ϩ��
sbit Latch1=P2^2;//������
sbit Latch2=P2^3;//λ����
int main()
{ 
	unsigned int count=0;//�������
	unsigned int second=0;//�����
	unsigned int minute=0;//�ּ���
	unsigned int hour=0;//ʱ����
	unsigned int LedCode=0;//����ܱ��
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
				if(second>=60)//��ʵ�ɣ�һ����=59s��-1s��ȥ�ˣ��׸������ˣ���������
				{
					second=0;
					minute++;
					if(minute>=60)
					{
						minute=0;
						hour++;
					}
				}
				LedBuff[0]=LedChar[second%10];//�ӵ͵��߽�����ת��Ϊ�������ʾ�ַ��͵���Ӧ�������
				LedBuff[1]=LedChar[second/10%10];
				LedBuff[2]=LedChar[minute%10];
				LedBuff[3]=LedChar[minute/10%10];
				LedBuff[4]=LedChar[hour%10];
				LedBuff[5]=LedChar[hour/10%10];
			}
				if(LedCode==0)
				{
					P0=0x7f;//����������ܣ��������
					Latch2=1;
					Latch2=0;
					LedCode++;
					P0=LedBuff[0];
					Latch1=1;
					Latch1=0;
				}
				else if(LedCode==1)//�м�һ�Ƚ�else if��д��if�������������ڼӳ���������������Բ��㡣
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
					LedCode=0;//һ����Ҫ��������ܣ�����Ҫ��ʱ���㣬��Ȼ��ȫ��������= =
					P0=LedBuff[5];
					Latch1=1;
					Latch1=0;
				}
			}
		}
	}