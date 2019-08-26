 
#include<reg51.h>

#define uchar unsigned char

sbit dula=P2^6; //申明U1锁存器的锁存端
sbit wela=P2^7;	 //申明U2锁存器的锁存端
//j、k用于声明延时变量
//c1、c0分别用于存储显示个位和十位的值
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

//a：显示十位
//b: 显示个位
void display(uchar a,uchar b)
{
   //显示个位
   dula=1;
   P0=table[a];
   delay(5);   
   dula=0;
   wela=1;
   P0=0xfe;
   wela=0;
  // delay(10);
  //显示十位,不能干扰个位，
  //所以只开启十位的显示,将将段选锁定，位选打开
     dula=1;
   	 P0=table[b];
	 delay(5);      
     dula=0;
     //开启位选 
     wela=1;
     P0=0xfd;
     wela=0;
     //delay(10);
}

//显示矩阵键盘按下的值
void displayKeyNum(uchar num)
{			
   P0=table[num];
   dula=1;
   dula=0;
}


//矩阵键盘扫描
void matrixkeyscan()
{
    uchar temp,key;
	P3=0xfe;   //扫描第一行按键
	temp=P3;
	temp=temp&0xf0;		 //判断temp高4位是否有0，如果temp的高4位有0那么	 temp的高4位数据实际上就是矩阵键盘的4个列线
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
		c0=key%10;		  //取出当前描述的个位与十位
		c1=key/10;
		display(c1,c0);	   //显示
		//displayKeyNum(key);
	  }
	
	}
	P3=0xfd;   //扫描第二行按键
	temp=P3;
	temp=temp&0xf0;		 //判断temp高4位是否有0，如果temp的高4位有0那么	 temp的高4位数据实际上就是矩阵键盘的4个列线
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
		c0=key%10;		  //取出当前描述的个位与十位
		c1=key/10;
		display(c1,c0);	   //显示
		//displayKeyNum(key);
	  }
	
	}

	P3=0xfb;   //扫描第三行按键
	temp=P3;
	temp=temp&0xf0;		 //判断temp高4位是否有0，如果temp的高4位有0那么	 temp的高4位数据实际上就是矩阵键盘的4个列线
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
		c0=key%10;		  //取出当前描述的个位与十位
		c1=key/10;
		display(c1,c0);	   //显示
		//displayKeyNum(key);
	  }
	
	}
	P3=0xf7;   //扫描第四行按键
	temp=P3;
	temp=temp&0xf0;		 //判断temp高4位是否有0，如果temp的高4位有0那么	 temp的高4位数据实际上就是矩阵键盘的4个列线
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
		c0=key%10;		  //取出当前描述的个位与十位
		c1=key/10;
		display(c1,c0);	   //显示
		//displayKeyNum(key);
	  }
	
	}

}


 //实现60秒计时
void main0()
{
	TMOD=0x01;		 //模式设置，00000001，可见采用的是定时器0，工作与模式1（M1=0，M0=1）。
	TR0=1;			 //打开定时器
	TH0=(65536-46080)/256;// 由于晶振为11.0592,故所记次数应为46080，计时器每隔50000微秒发起一次中断。
	TL0=(65536-46080)%256;//46080的来历，为50000*11.0592/12
	ET0=1;			 //开定时器0中断
	EA=1;			 //开总中断
	while(1)
	{
		//1秒钟过去
		if(pp==20)
		{
		   //将记录1秒是否到的变量归零
			pp=0;
			//秒数加1
			m++;
			n--;
			P1=n;//闪烁灯
			if(m==60)
			{
				m=0;	   //若到了60s，则归零
			}
		}
		c0=m%10;		  //取出当前描述的个位与十位
		c1=m/10;
		display(c1,c0);	   //显示
	}
}

 //实现矩阵键盘扫描
 void main1()
 {

	while(1)
	{
     	matrixkeyscan();
	}
 
 }


//流水灯
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