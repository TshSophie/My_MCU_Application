 
#include<reg51.h>

#define uchar unsigned char

sbit dula=P2^6; //����U1�������������
sbit wela=P2^7;	 //����U2�������������
//j��k����������ʱ����
//c1��c0�ֱ����ڴ洢��ʾ��λ��ʮλ��ֵ
unsigned char j,k,c1,c0,m,n=255;
unsigned char pp;
unsigned char code table[]={0xc0,0xf9,0xa4,0xb0,//0~3
0x99,0x92,0x82,0xf8,//4~7
0x80,0x90,0x88,0x83,//8~b
0xc6,0xa1,0x86,0x8e //c~f
};

void delay(unsigned char i)
{
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}

//a����ʾʮλ
//b: ��ʾ��λ
void display(uchar a,uchar b)
{
   //��ʾ��λ
   dula=1;
   P0=table[a];
   delay(5);   
   dula=0;
   wela=1;
   P0=0xfe;
   wela=0;
  // delay(10);
  //��ʾʮλ,���ܸ��Ÿ�λ��
  //����ֻ����ʮλ����ʾ,������ѡ������λѡ��
     dula=1;
   	 P0=table[b];
	 delay(5);      
     dula=0;
     //����λѡ 
     wela=1;
     P0=0xfd;
     wela=0;
     //delay(10);
}

//��ʾ������̰��µ�ֵ
void displayKeyNum(uchar num)
{			
   P0=table[num];
   dula=1;
   dula=0;
}


//�������ɨ��
void matrixkeyscan()
{
    uchar temp,key;
	P3=0xfe;   //ɨ���һ�а���
	temp=P3;
	temp=temp&0xf0;		 //�ж�temp��4λ�Ƿ���0�����temp�ĸ�4λ��0��ô	 temp�ĸ�4λ����ʵ���Ͼ��Ǿ�����̵�4������
	if(temp==0xf0)
	{
	 delay(10);
	 temp=P3;
	 temp=temp&0xf0;
	  if(temp!=0xf0)
	  {
	  	 temp=P3;
		 switch(temp)
		 {
		 	case 0xee:
			key=0;
			break;

			case 0xde:
			key=1;
			break;

			case 0xbe:
			key=2;
			break;

			case 0x7e:
			key=3;
			break;
		 }

		while(temp!=0xf0)
		{
		  temp=P3;
		  temp=temp&0xf0;		
		}
		c0=key%10;		  //ȡ����ǰ�����ĸ�λ��ʮλ
		c1=key/10;
		display(c1,c0);	   //��ʾ
		//displayKeyNum(key);
	  }
	
	}
	P3=0xfd;   //ɨ��ڶ��а���
	temp=P3;
	temp=temp&0xf0;		 //�ж�temp��4λ�Ƿ���0�����temp�ĸ�4λ��0��ô	 temp�ĸ�4λ����ʵ���Ͼ��Ǿ�����̵�4������
	if(temp==0xf0)
	{
	 delay(10);
	 temp=P3;
	 temp=temp&0xf0;
	  if(temp!=0xf0)
	  {
	  	 temp=P3;
		 switch(temp)
		 {
		 	case 0xed:
			key=4;
			break;

			case 0xdd:
			key=5;
			break;

			case 0xbd:
			key=6;
			break;

			case 0x7d:
			key=7;
			break;
		 }

		while(temp!=0xf0)
		{
		  temp=P3;
		  temp=temp&0xf0;		
		}
		c0=key%10;		  //ȡ����ǰ�����ĸ�λ��ʮλ
		c1=key/10;
		display(c1,c0);	   //��ʾ
		//displayKeyNum(key);
	  }
	
	}

	P3=0xfb;   //ɨ������а���
	temp=P3;
	temp=temp&0xf0;		 //�ж�temp��4λ�Ƿ���0�����temp�ĸ�4λ��0��ô	 temp�ĸ�4λ����ʵ���Ͼ��Ǿ�����̵�4������
	if(temp==0xf0)
	{
	 delay(10);
	 temp=P3;
	 temp=temp&0xf0;
	  if(temp!=0xf0)
	  {
	  	 temp=P3;
		 switch(temp)
		 {
		 	case 0xeb:
			key=8;
			break;

			case 0xdb:
			key=19;
			break;

			case 0xbb:
			key=10;
			break;

			case 0x7b:
			key=11;
			break;
		 }

		while(temp!=0xf0)
		{
		  temp=P3;
		  temp=temp&0xf0;		
		}
		c0=key%10;		  //ȡ����ǰ�����ĸ�λ��ʮλ
		c1=key/10;
		display(c1,c0);	   //��ʾ
		//displayKeyNum(key);
	  }
	
	}
	P3=0xf7;   //ɨ������а���
	temp=P3;
	temp=temp&0xf0;		 //�ж�temp��4λ�Ƿ���0�����temp�ĸ�4λ��0��ô	 temp�ĸ�4λ����ʵ���Ͼ��Ǿ�����̵�4������
	if(temp==0xf0)
	{
	 delay(10);
	 temp=P3;
	 temp=temp&0xf0;
	  if(temp!=0xf0)
	  {
	  	 temp=P3;
		 switch(temp)
		 {
		 	case 0xe7:
			key=12;
			break;

			case 0xd7:
			key=13;
			break;

			case 0xb7:
			key=14;
			break;

			case 0x77:
			key=15;
			break;
		 }

		while(temp!=0xf0)
		{
		  temp=P3;
		  temp=temp&0xf0;		
		}
		c0=key%10;		  //ȡ����ǰ�����ĸ�λ��ʮλ
		c1=key/10;
		display(c1,c0);	   //��ʾ
		//displayKeyNum(key);
	  }
	
	}

}


 //ʵ��60���ʱ
void main0()
{
	TMOD=0x01;		 //ģʽ���ã�00000001���ɼ����õ��Ƕ�ʱ��0��������ģʽ1��M1=0��M0=1����
	TR0=1;			 //�򿪶�ʱ��
	TH0=(65536-46080)/256;// ���ھ���Ϊ11.0592,�����Ǵ���ӦΪ46080����ʱ��ÿ��50000΢�뷢��һ���жϡ�
	TL0=(65536-46080)%256;//46080��������Ϊ50000*11.0592/12
	ET0=1;			 //����ʱ��0�ж�
	EA=1;			 //�����ж�
	while(1)
	{
		//1���ӹ�ȥ
		if(pp==20)
		{
		   //����¼1���Ƿ񵽵ı�������
			pp=0;
			//������1
			m++;
			n--;
			P1=n;//��˸��
			if(m==60)
			{
				m=0;	   //������60s�������
			}
		}
		c0=m%10;		  //ȡ����ǰ�����ĸ�λ��ʮλ
		c1=m/10;
		display(c1,c0);	   //��ʾ
	}
}

 //ʵ�־������ɨ��
 void main1()
 {

	while(1)
	{
     	matrixkeyscan();
	}
 
 }


//��ˮ��
void main()
{
	unsigned char m=255;
	while(1)
	{
		P1=m;
		delay(2000);
		m--;
	}
}

void time0() interrupt 1
{TH0=(65536-46080)/256;
	TL0=(65536-46080)%256;
	pp++;
}