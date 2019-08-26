#include  <reg51.h>
#include <intrins.h>
#define  uchar  unsigned  char
sbit  RS=P1^7;
sbit  RW=P1^6;
sbit  E=P1^5;
sbit PIN_LED = P1^1; // ������
sbit PIN_CLEAR = P3^4; // ����
sbit PIN_BEE_BTN = P3^5; // ��������ť
sbit PIN_BEE = P1^0;

void  init(void);
void  wc51r(uchar  i);
void  wc51ddr(uchar  i);
void  fbusy(void);
void showText(char *str);
void switchAndshow(int num);
void delay();

int num = 0; // ͳ�Ƽ�ʱ����
int minutes = 0; // ����
int seconds = 0; // ����
int percent_second = 0; // �ٷ���

int flag = 0;	// led�źŵ�
char * status_text[] = {"WAIT ","START","PAUSE","CLEAR"}; // ��ʾ״̬��Ϣ
int status = 0;	 // ״̬����

char * sound_text[] = {"OFF","ON "}; // ������ʾ״̬��Ϣ
int sound = 0; // �Ƿ�������,Ĭ�Ͽ���

void timer_init()
{
	TMOD=0x90;    				//���ö�ʱ��1������ʽ1
	TH1=(65536-9216)/256;	    //װ��ֵ,10����   10000*11.0592/12  = 9216
	TL1=(65536-9216)%256;
	EA=1;    //�����ж�
	EX0 = 1; // �ⲿ�ж�0	
	IT0 = 1; // �ⲿ�ж�0���½��ش���
	EX1 = 1; // �ⲿ�ж�1	
	IT1 = 1; // �ⲿ�ж�1���½��ش���
	ET1=1;	  //����ʱ��1�ж�	
	TR1=0;	  //�ر�/������ʱ��1	
}


//��ʼ������
void lcd_init()
{
	wc51r(0x01);     	//����
	wc51r(0x38);      	//ʹ��8λ����,��ʾ����,ʹ��5��7������
	wc51r(0x0c);     	//��ʾ����,����,�ַ�����˸
	wc51r(0x06);     	//�ַ�����,����Զ�����һ��
}

//������
void  main()
{		  
	SP=0x50;
	lcd_init();
	timer_init();	
	status = 0;
	while(1)
	{
	   // �������㰴ť
	   if(!PIN_CLEAR)
	   {
	   	   status = 3;
		   minutes = 0; // ����
		   seconds = 0; // ����
		   percent_second = 0; // �ٷ���
		   PIN_BEE = 1;
		   TR1=0;	  //�ر�/������ʱ��1	
		   TH1=(65536-9216)/256;	    //װ��ֵ,10����   10000*11.0592/12  = 9216
		   TL1=(65536-9216)%256;
	   }

	   // �����������ư�ť
	   if(!PIN_BEE_BTN)
	   {	    		   	 		 
		 sound = 1;			 					 		 		 		 	   
	   }else{	   		
		 sound = 0;
	   }
	   wc51r(0x81);       	//д����ʾ��������ʼ��ַΪ��1�е�2��
	   showText("S:");
	   showText(status_text[status]);
	   showText(" VU:");	  
	   showText(sound_text[sound]);

	   wc51r(0xc1);     	//д����ʾ��������ʼ��ַΪ��2�е�2��	  
	   showText("TIME:");	   
	   switchAndshow(minutes);
	   showText(":");	   
	   switchAndshow(seconds);
	   showText(".");	   
	   switchAndshow(percent_second);

	   PIN_LED = flag; // ������
	}
}

// �ⲿ�ж�0 ��ʼ��ʱ
void int_0(void) interrupt 0
{	
   status = 1; 
   TR1 = 1;	  //�ر�/������ʱ��1 
}

// �ⲿ�ж�1 ��ͣ��ʱ
void int_1(void) interrupt 2
{	
   status = 2;
   PIN_BEE = 1;
   TR1 = 0;	  //�ر�/������ʱ��1  
}

// //��ʱ��0 
void T1_time()interrupt 3 				  
{
   TH1=(65536-9216)/256;	    //װ��ֵ,10����   10000*11.0592/12  = 9216
   TL1=(65536-9216)%256;

   num++;                //numÿ��1���ж��Ƿ�100��
   percent_second++;
   if(num==100)          //�������100�Σ�˵��1��ʱ�䵽
   {
   	 percent_second = 0;
     seconds++; // ����++
	 
	 if(sound == 1)
	 {
	   PIN_BEE = flag; // ��ʾ��	 
	 }else{
	    PIN_BEE = 1;
	 }	 	  	  
	 if(seconds == 60)
	 {
	   seconds = 0;
	   minutes++; // ����++	
	 }
     num = 0;						//Ȼ���num���������ټ�100��
	 flag = !flag;           //�÷��������״̬ȡ��	 
   }		
} 

// ����ת������-��λ��ʾ����ֵ
void switchAndshow(int num)
{		
	// 00						
	int shi = num / 10 ; 
	int ge = num % 10; 						  	     		  
	wc51ddr(shi + 48);		
    wc51ddr(ge + 48);					
}

// ��ʾ����
void showText(char *str)
{
 while(*str)
 {
 	char cur = *str;
	str++;
	wc51ddr(cur);	 
 }
}

//���æ����
void  fbusy()
{
	P2=0Xff;RS=0;RW=1;
	E=0; E=1;
	while (P2&0x80){E=0;E=1;}      //æ,�ȴ�
}

//д�����
void  wc51r(uchar  j)
{
	fbusy();
	E=0;RS=0;RW=0;
	E=1;
	P2=j;
	E=0;
}

//д���ݺ���
void  wc51ddr(uchar  j)
{
	fbusy();
	E=0;RS=1;RW=0;
	E=1;
	P2=j;
	E=0;
}

