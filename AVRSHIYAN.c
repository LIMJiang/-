//#include "avr/io.h"
         //����AVR��Ƭ���Ĵ��������ͷ�ļ�   
         #include <mega16.h> 
#include "NBCAVR.h"         //����λ������ͷ�ļ�

#define uchar unsigned char
#define uint  unsigned int

#define LED_Data  PORTB
#define Dataport PORTC
#define LED_1 PIOD4
#define LED_2 PIOD5
#define LED_3 PIOD6
#define LED_4 PIOA6

#define S1 PIOD2           //���尴��IO
#define S2 PIOD0          
#define S3 PIOD3          
#define S4 PIOD1         
#define S5 PIOA7





flash char led_7[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
//flash char position[6]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf};
//flash char position[4]={0xff,0xbf,0xdf,0xef};
flash char position[4]={0xc3,0xc3,0xa3,0x93};
flash char positiona[4]={0x43,0x03,0x03,0x03};                                      // λѡPORTA
uchar resit[8]={0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE};

int i=0;
//int time_counter; // �жϴ���������Ԫ
char posit;
bit point_on, time_1s_ok;

char time[2]; // ʱ���֡������
char dis_buff[4]; // ��ʾ�����������Ҫ��ʾ�� 6 ���ַ��Ķ���ֵ
uint time_counter; // 1 �������
//bit point_on; // ����ʾ��־



uchar keyValue;             //����ɨ��������
//uchar  dis[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
             //  0    1    2    3    4    5    6    7
              // 0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};//0~F�Ķ���
             //  8    9    A    B    C    D    E    F








uchar keyValue;             //����ɨ��������
uchar  dis[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
             //  0    1    2    3    4    5    6    7    
               0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};//0~F�Ķ���
             //  8    9    A    B    C    D    E    F  

uchar aa; //Ƭѡ
uchar bb;//�ַ�
uchar cc;//�ź���
uchar dd;


//***********************************************************************************
//��ʱ
//***********************************************************************************
void delay(uint time)
{
	uint i,j;
	for(i = 0;i < time; i++)
	{
	  for(j = 0;j < 30; j++);
    }
}

//***********************************************************************************
//IO��ʼ������
//***********************************************************************************
void IO_init(void)
{
    DDRB =0xFF;            //����PB��Ϊ���
	DDRD.7=1;        //������
    DDRC =0xFF;            //����PC��Ϊ���

	DDRD =0xf0;    //����PD��Ϊ����
	PORTD=0x0f;    //����PD����

    
    PORTC = 0x00;
    DDRC = 0xff;
     PORTA = 0x00;

    DDRA = 0x40;
    PORTB = 0xff;
    DDRB = 0xff;



}













  void display() // ɨ����ʾ������ִ��ʱ�� 12ms
{
    PORTA.6=0;
    PORTD =0x03;
 //char i;
 //for(i=0;i<=3;i++)
 //{
 PORTC = led_7[dis_buff[posit]];
 if (point_on && posit==2) PORTC |= 0x80; // (1)

 //PORTD = position[posit];
 //PORTA = positiona[posit];  
 
 
 if(posit==0)
    {
       PORTA.6=1; 
    }
    else
    {
       PORTD = position[posit];
    }
 
 
 
 //delay_ms(2); // (2)
 //PORTC = 0xff; // (3)
 if(++posit >= 4)
    {
        posit = 0;
    }
 //}
}






interrupt [TIM0_COMP] void timer0_comp_isr(void)                                  
{
 display(); // ���� LED ɨ����ʾ
 if (++time_counter>=500)
 {
 time_counter = 0;
 time_1s_ok = 1;
 }
}








void time_to_disbuffer(void) // ʱ��ֵ����ʾ����������
{
 char i,j=0;
 for (i=0;i<=1;i++)
 {
 dis_buff[j++] = time[i] % 10;
 dis_buff[j++] = time[i] / 10;
 }
}






















void keyScan()                             
 {
//    PORTD=0x00;
    uchar x,y; 
    DDRD =0x03;                      //����PD�ڸ�4λΪ����
    PORTD=0x0c;                      //����PD��4λ����,��ʱPIND��4λȫ1
    if((PIND&0x0c)!=0x0c)        //�ж��Ƿ��а�������
    {
     delay(20);                  //��ʱ����
     if((PIND&0x0c)!=0x0c)       //�ٴ��ж��Ƿ��а�������
	   {
//	   PORTB=0x0f;
       x=(PIND&0x0c);
       DDRD =0x0c;                      

    aa=aa%8; 
    aa++;

    bb=bb%10;
      bb++;
   
       delay(5);
       y=(PIND&0x03);
       keyValue=x|y;
       while((PIND&0x03)!=0x03); 
       }     

       //�ȴ������ɿ�
       
//       PORTB=0xf0;
    }
 }

 void keyHandle()                     
 {      
        switch(keyValue)         
          {
            case 0x06:                 //S17            ��
                {
                  PORTB=0XFF;
                  time_1s_ok = 0; 
                  
                 break;          
                }
            case 0x0a:                 //S18           ��
                {
                 PORTB=led_7[bb];;       
                 time_1s_ok = 0;
                 time[1]=0;
                 time[0]=0;
                 break;
                }
            case 0x05:                 //S19         ��
                {  
                 
                     time_1s_ok = 1;       //�����
                
                     
                 break;
                }
            case 0x09:                 //S20           ��
                {    
                PORTB=resit[aa];
                
              
                
                
                
               
                   
               
                
                 break;
                }
            default:
//                 PORTB=0xf0;
         break;
          }
 }

//***********************************************************************************
//������
//***********************************************************************************
void main()
{      
    IO_init();                //IO��ʼ��
    PORTB=0xff;      
    
    
    
    
    TCCR0=0x0b; // �ڲ�ʱ�ӣ�64 ��Ƶ��2M/64=31.25KHz����CTC ģʽ
    TCNT0=0x00; 
    OCR0=0x7C; //125/31.25=4ms//��������
    TIMSK=0x02; // ���� T/C0 �Ƚ�ƥ���ж�

     #asm("sei");
    
    
    
    
    
    
    
    
    
    
    
    
    
    while(1)                  //��ѭ��
     {
 //     PORTB=0xff;
//      PORTC=0x66;
/*      LED_1=1;
      LED_2=1;
      LED_3=1;
      LED_4=1;*/
     keyScan();             //����ɨ��
     keyHandle();           //��������
     display(); 
     display(); 
      display(); 
      keyScan();             //����ɨ��
      keyHandle();           //��������
     
     
       if (time_1s_ok) // 1 �뵽
      {
        time_1s_ok = 0;
        point_on = ~point_on;  
        if(i>=1)
        {    
            if(time[0]>=31) 
            {PORTB=0xff;  
            PORTD.7=0;}
            else if(time[0]%2==0) 
            {PORTB = 0x00; 
            PORTD.7=1;}
            else
           { PORTB = 0xff; 
            PORTD.7=0;}
             
        }
        if (++time[0] >= 60) // ����ʱ�����
        {
            time[0] = 0;
            //PORTD.7=1;  
             i++;
            if (++time[1] >= 60)
            {
                time[1] = 0;
                //if (++time[2] >= 24) time[2] = 0;
            }
        }
        time_to_disbuffer(); // �µ����õ�ʱ������ʾ������
      }
   
     

     
     }  
}