/*
����ܼ�ʱ��
(C)2017 Richard Kuroshio
������ѩ�ɡ��ְ��ֽ���ѧ51��Ƭ�����͵·���LY-51S������ʵ��
��֪ʲôԭ���ʱ�ٶ����Լӿ죿��֪�Ƿ�;��񾫶��й�
*/
#include<reg51.h>
unsigned char code LedChar[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//������ַ���
unsigned char LedBuff[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//��ʾ���������ܳ�ʼֵ����ֹ������ȫ��Ϩ�𡣲��ܼ�code����Ȼֻ�ܶ������޸ĸ�ֵ��
sbit Latch1=P2^2;//������
sbit Latch2=P2^3;//λ����
unsigned int count=0;//�������
unsigned int LedCode=0;//����ܱ��
//���������������������ܵ�- -b
int main()
{
	unsigned long second=0;//�������long��
	EA=1;//�ж�ʹ��
	TMOD=0x01;//T0 ģʽ1��16λ������
	TH0=0xfc;
	TL0=0x67;//0xfc67 1ms
	TR0=1;
	ET0=1;//T0�ж�ʹ��
	while(1)
	{

		if(count>=1000)//1000ms=1s
		{
			count=0;
			second++;
			LedBuff[0]=LedChar[second%10];//�ӵ͵��߽�����ת��Ϊ�������ʾ�ַ��͵���Ӧ�������
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
void InterrptTimer0() interrupt 1//T0�жϴ���
{
	TH0=0xfc;
	TL0=0x67;
	count++;//�жϼ�����ÿ1ms����һ��
	P0=0x00;//���������
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