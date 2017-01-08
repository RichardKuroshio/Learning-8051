#include<reg51.h>
#include<intrins.h>
sbit RCLK_J4=P2^2;
sbit SRCLK_J4=P2^1;
sbit SER_J4=P2^0;
sbit RCLK_J5=P1^0;
sbit SRCLK_J5=P1^1;
sbit SER_J5=P1^2;
unsigned char tab[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};//�趨�ڼ�����ʾ
void SendByte(unsigned int dat)//���ݷ��ͳ���
{
	unsigned int loop;
	for(loop=0;loop<8;loop++)
	{
		SRCLK_J5=0;
		SER_J5=dat&0x80;
		dat<<=1;
		SRCLK_J5=1;
	}
}
void LatchOutput(void)//�����������
{
	RCLK_J5=0;
	_nop_();
	RCLK_J5=1;
}
void SendSeg(unsigned int dat)//�����˿��Ƴ���
{
	unsigned int loop;
	for(loop=0;loop<8;loop++)
	{
		SRCLK_J4=0;
		SER_J4=dat&0x80;
		dat<<=1;
		SRCLK_J4=1;
	}
	RCLK_J4=0;
	_nop_();
	RCLK_J4=1;
}
void DelayUs2x(unsigned char t)//��ʱ����
{   
 while(--t);
}
void DelayMs(unsigned char t)
{ 
 while(t--)
 {
   DelayUs2x(245);
	 DelayUs2x(245);
 }
}
int main()//������
{
	unsigned int loop;
	while(1)
	{
		for(loop=0;loop<8;loop++)
		{
			SendSeg(~tab[loop]);
			SendByte(0xff);//ÿһ�ж���01010101��ʾ
			SendByte(0x55);
			LatchOutput();
			DelayMs(1);
			SendByte(0xff);//ȫ��Ϩ�𣬷�ֹ��Ӱ��
			SendByte(0xff);
			
			LatchOutput();
			DelayMs(1);
		}
	}
}