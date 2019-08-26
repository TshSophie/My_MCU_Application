#include  <reg51.h>
#include <intrins.h>
#define  uchar  unsigned  char
sbit  RS=P1^7;
sbit  RW=P1^6;
sbit  E=P1^5;
sbit PIN_LED = P1^1; // 呼吸灯
sbit PIN_CLEAR = P3^4; // 清零
sbit PIN_BEE_BTN = P3^5; // 蜂鸣器按钮
sbit PIN_BEE = P1^0;

void  init(void);
void  wc51r(uchar  i);
void  wc51ddr(uchar  i);
void  fbusy(void);
void showText(char *str);
void switchAndshow(int num);
void delay();

int num = 0; // 统计计时次数
int minutes = 0; // 分钟
int seconds = 0; // 秒种
int percent_second = 0; // 百分秒

int flag = 0;	// led信号灯
char * status_text[] = {"WAIT ","START","PAUSE","CLEAR"}; // 提示状态信息
int status = 0;	 // 状态代号

char * sound_text[] = {"OFF","ON "}; // 声音提示状态信息
int sound = 0; // 是否开启声音,默认开启

void timer_init()
{
	TMOD=0x90;    				//设置定时器1工作方式1
	TH1=(65536-9216)/256;	    //装初值,10毫秒   10000*11.0592/12  = 9216
	TL1=(65536-9216)%256;
	EA=1;    //开总中断
	EX0 = 1; // 外部中断0	
	IT0 = 1; // 外部中断0，下降沿触发
	EX1 = 1; // 外部中断1	
	IT1 = 1; // 外部中断1，下降沿触发
	ET1=1;	  //开定时器1中断	
	TR1=0;	  //关闭/启动定时器1	
}


//初始化函数
void lcd_init()
{
	wc51r(0x01);     	//清屏
	wc51r(0x38);      	//使用8位数据,显示两行,使用5×7的字型
	wc51r(0x0c);     	//显示器开,光标关,字符不闪烁
	wc51r(0x06);     	//字符不动,光标自动右移一格
}

//主函数
void  main()
{		  
	SP=0x50;
	lcd_init();
	timer_init();	
	status = 0;
	while(1)
	{
	   // 监听清零按钮
	   if(!PIN_CLEAR)
	   {
	   	   status = 3;
		   minutes = 0; // 分钟
		   seconds = 0; // 秒种
		   percent_second = 0; // 百分秒
		   PIN_BEE = 1;
		   TR1=0;	  //关闭/启动定时器1	
		   TH1=(65536-9216)/256;	    //装初值,10毫秒   10000*11.0592/12  = 9216
		   TL1=(65536-9216)%256;
	   }

	   // 监听声音控制按钮
	   if(!PIN_BEE_BTN)
	   {	    		   	 		 
		 sound = 1;			 					 		 		 		 	   
	   }else{	   		
		 sound = 0;
	   }
	   wc51r(0x81);       	//写入显示缓冲区起始地址为第1行第2列
	   showText("S:");
	   showText(status_text[status]);
	   showText(" VU:");	  
	   showText(sound_text[sound]);

	   wc51r(0xc1);     	//写入显示缓冲区起始地址为第2行第2列	  
	   showText("TIME:");	   
	   switchAndshow(minutes);
	   showText(":");	   
	   switchAndshow(seconds);
	   showText(".");	   
	   switchAndshow(percent_second);

	   PIN_LED = flag; // 呼吸灯
	}
}

// 外部中断0 开始计时
void int_0(void) interrupt 0
{	
   status = 1; 
   TR1 = 1;	  //关闭/启动定时器1 
}

// 外部中断1 暂停计时
void int_1(void) interrupt 2
{	
   status = 2;
   PIN_BEE = 1;
   TR1 = 0;	  //关闭/启动定时器1  
}

// //定时器0 
void T1_time()interrupt 3 				  
{
   TH1=(65536-9216)/256;	    //装初值,10毫秒   10000*11.0592/12  = 9216
   TL1=(65536-9216)%256;

   num++;                //num每加1此判断是否到100次
   percent_second++;
   if(num==100)          //如果到了100次，说明1秒时间到
   {
   	 percent_second = 0;
     seconds++; // 秒钟++
	 
	 if(sound == 1)
	 {
	   PIN_BEE = flag; // 提示音	 
	 }else{
	    PIN_BEE = 1;
	 }	 	  	  
	 if(seconds == 60)
	 {
	   seconds = 0;
	   minutes++; // 分钟++	
	 }
     num = 0;						//然后把num清零重新再计100次
	 flag = !flag;           //让发光二极管状态取反	 
   }		
} 

// 数据转换函数-两位显示计数值
void switchAndshow(int num)
{		
	// 00						
	int shi = num / 10 ; 
	int ge = num % 10; 						  	     		  
	wc51ddr(shi + 48);		
    wc51ddr(ge + 48);					
}

// 显示文字
void showText(char *str)
{
 while(*str)
 {
 	char cur = *str;
	str++;
	wc51ddr(cur);	 
 }
}

//检查忙函数
void  fbusy()
{
	P2=0Xff;RS=0;RW=1;
	E=0; E=1;
	while (P2&0x80){E=0;E=1;}      //忙,等待
}

//写命令函数
void  wc51r(uchar  j)
{
	fbusy();
	E=0;RS=0;RW=0;
	E=1;
	P2=j;
	E=0;
}

//写数据函数
void  wc51ddr(uchar  j)
{
	fbusy();
	E=0;RS=1;RW=0;
	E=1;
	P2=j;
	E=0;
}

