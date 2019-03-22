#include "user_conf.h"
#include "user_time.h"

uint32_t uart2BaudRate = 9600;//����2ͨ�Ų�����


extern void ringBuf_put(u8 data);
extern void scanCodeSend(void);
extern void scanCodeTimeOut (void);
extern volatile u8 g_usart2Pack;
extern u8 host2Scan;
extern u8 host2Voice;
extern u8 scanWaitTimeout;
extern u8 voiceWaitTimeout;

extern DISPLAY DisplayArea[];
extern SCREEN Screen;
extern UART_RCV_T  UART2_RCV_S;

//����ɨ��ͷ����ɨ�뼰�ر�ɨ�빦��
//������cmd:  ENABLE ��ʼɨ�����Disable  ֹͣɨ�����
void scanCodeCtrl(uint8_t cmd);

void scanCamera(void)
{
	static uint32_t tick;
	static u8 cnt = 0;
	
	if (cnt == 0) {
		cnt = 1;
		FirstPage();
	}
	
	if (host2Scan == 1) {
	//if (1) {
		if (UART5_RCV_S.SuccessFlag==1)
		{
			UART5_RCV_S.SuccessFlag = 0;	
			host2Scan = 0;
			scanCodeSend();
			return ;
		}
		if (UART4_RCV_S.SuccessFlag==1)
		{
			UART4_RCV_S.SuccessFlag = 0;	
			host2Scan = 0;
			scanCodeSend();
			return ;
		}	
		if (UART1_RCV_S.SuccessFlag==1)
		{
			UART1_RCV_S.SuccessFlag = 0;
			host2Scan = 0;
			scanCodeSend();
			return ;
		}
		
		if (scanWaitTimeout == 1) {
			host2Scan = 0;
			scanCodeTimeOut();	
			FirstPage();
		}
	}
	else {
		UART5_RCV_S.SuccessFlag = 0;
		UART4_RCV_S.SuccessFlag = 0;
		UART1_RCV_S.SuccessFlag = 0;
	}
}



//DisplayArea[i].mode��ʾģʽ

//#define MOVE_STATIC  	  0x0
//#define MOVE_UPIN  		  0x11
//#define MOVE_UPOUT  	  0x12
//#define MOVE_UPCYC  	  0x13
//#define MOVE_LEFTIN  		0x21
//#define MOVE_LEFTOUT    0x22
//#define MOVE_LEFTCYC    0x23
//#define MOVE_RIGHTIN		0x31
//#define MOVE_RIGHTOUT		0x32
//#define MOVE_RIGHTCYC		0x33

//#define MOVE_DOWN		    0x43
//#define MOVE_LEFTUP   	0x53
//#define MOVE_RIGHTUP  	0x63
//#define MOVE_LEFTSTATIC 0x01   //��̬���ƶ������̫�������
//#define MOVE_UPSTATIC  	0x02     //��̬���ƶ����߶�̫���Ϲ���
//#define MOVE_CLEAR  	  0xff
//��ҳ��ʾ
void FirstPage(void)
{
	unsigned char i;	
	char temp[40]={0};
	//����Ĭ������
	//����Ĭ�ϳ�ʼ������������1��2��3��4��
	for(i=0;i<4;i++)
	{
		DisplayArea[i].y= i*16;//������������ʼ��
		DisplayArea[i].x= 0;//�����������ʼ��
		DisplayArea[i].h= 16;//����߶ȣ����ص㣩��
		DisplayArea[i].w= 64;//�����ȣ����ص㣩��
		DisplayArea[i].type = 0;//��ʾ���ͣ�0��ʾ�ַ���1����ʾͼƬ
		DisplayArea[i].mode = 0;//0:��̬��ʾ,1,��̬���ƶ������̫���������2: //��̬���ƶ����߶�̫���Ϲ���
		DisplayArea[i].speed = 2;//ȡֵ��Χ��0-6��
		DisplayArea[i].col = 0;//��ʾ��ɫ��0����ɫ��1����ɫ
		
		DisplayArea[i].movexx =0;//����
		DisplayArea[i].movex =0;//����
		DisplayArea[i].moveyy =0;//����
		DisplayArea[i].movey =0;//����
		DisplayArea[i].bufsize =0;//����
		Screen.col = DisplayArea[i].col;
		DisplayArea[i].enable =1;
		if(DisplayArea[i].fontbuf != NULL)
		{
			myfree(DisplayArea[i].fontbuf);//�ͷŷ�������	
			DisplayArea[i].fontbuf = NULL;
		}
		//��ʾ����
		DisplayArea[i].fh= 16;//������ʵ����ʾ���ݸ߶ȣ����1��16���������32������48,4��64
		DisplayArea[i].fw= 64;//������ʵ����ʾ���ݿ�ȣ�һ������Ϊ16����һ���ַ�Ϊ8.
		DisplayArea[i].bufsize = (((DisplayArea[i].fh>>4)*(DisplayArea[i].fw>>3))<<4);//5������ ��Ҫ160���ֽڵĿռ�
		DisplayArea[i].fontbuf = mymalloc(DisplayArea[i].bufsize);	
		if(DisplayArea[i].fontbuf !=0)
		{
			mymemset(DisplayArea[i].fontbuf,0,DisplayArea[i].bufsize);
			DisplayArea[i].upflag = 1;
			DisplayArea[i].enable = 1;		
			if(i==0)
			{
				memset(temp,0,sizeof(temp));
				sprintf(temp,"��ӭʹ��"),
				GetFont(temp,8,DisplayArea[0].fontbuf);//��ȡ��ģ��������Ϣ��������fontbuf������							
			}
			else if(i==1)
			{
				//�ڶ�����ʾ����
				memset(temp,0,sizeof(temp));
				sprintf(temp,"ɽ������"),
				GetFont(temp,8,DisplayArea[1].fontbuf);//��ȡ��ģ��������Ϣ��������fontbuf������					
			}
			else if(i==2)
			{
				//��������ʾ����
				memset(temp,0,sizeof(temp));
				sprintf(temp,"ɨ��֧��"),										
				GetFont(temp,8,DisplayArea[2].fontbuf);//��ȡ��ģ��������Ϣ��������fontbuf������					
			}
			else if(i==3)
			{
				//��������ʾ����
				memset(temp,0,sizeof(temp));
				sprintf(temp,"�����ն�"),															
				GetFont(temp,8,DisplayArea[3].fontbuf);//��ȡ��ģ��������Ϣ��������fontbuf������				
			}
		}			
	}
}
//֧��ҳ����ʾ
void PaymentPage(void)
{
	unsigned char i;	
	char temp[40]={0};
 	for(i=0;i<DISPLAY_AREA_MAX;i++)
	{
		if(DisplayArea[i].enable)
		{						
			if(DisplayArea[i].fontbuf)//
			{
				DisplayClearProcess(&DisplayArea[i]);
				myfree(DisplayArea[i].fontbuf);
				DisplayArea[i].fontbuf=NULL;
			}			
			DisplayArea[i].fontbuf = (unsigned char *)mymalloc((((DisplayArea[i].fh>>4)*(DisplayArea[i].fw>>3))<<4));			
//		DisplayArea[i].fontbuf = (unsigned char *)mem_mymalloc(DisplayArea[i].bufsize);
			if(DisplayArea[i].fontbuf==NULL)
			{
				//u1_printf("mem_mymalloc fail!\r\n"); 
				return ;
			}                
			mymemset(DisplayArea[i].fontbuf,0,DisplayArea[i].bufsize);
			DisplayArea[i].upflag = 1;
			//u1_printf("read area id:%d x:%d y:%d w:%d h:%d bufsize:%d\r\n",i+1,DisplayArea[i].x,DisplayArea[i].y,DisplayArea[i].w,DisplayArea[i].h,DisplayArea[i].bufsize);
		}
	}
	//����Ĭ������
	//����Ĭ�ϳ�ʼ������������1��2��3��4��
	for(i=0;i<4;i++)
	{
		DisplayArea[i].y= i*16;
		DisplayArea[i].x= 0;
		DisplayArea[i].h= 0x10;//ScreenArea->h
		DisplayArea[i].w= 0x40;
		DisplayArea[i].type = 0;//��ʾ�ַ�
		DisplayArea[i].mode = 0;//��̬��ʾ
		DisplayArea[i].speed = 2;//ȡֵ��Χ��0-6��
		
		DisplayArea[i].movexx =0;
		DisplayArea[i].movex =0;
		DisplayArea[i].moveyy =0;
		DisplayArea[i].movey =0;
		DisplayArea[i].bufsize =0;
		DisplayArea[i].col = 1;
		Screen.col = DisplayArea[i].col;
		DisplayArea[i].enable =1;
		if(DisplayArea[i].fontbuf != NULL)
		{
			myfree(DisplayArea[i].fontbuf);//�ͷŷ�������	
			DisplayArea[i].fontbuf = NULL;
		}
		//��ʾ����
		DisplayArea[i].fh= 16;
		DisplayArea[i].fw= 64;			
		DisplayArea[i].bufsize = (((DisplayArea[i].fh>>4)*(DisplayArea[i].fw>>3))<<4);//5������ ��Ҫ160���ֽڵĿռ�
		DisplayArea[i].fontbuf = mymalloc(DisplayArea[i].bufsize);	
		if(DisplayArea[i].fontbuf !=0)
		{
			mymemset(DisplayArea[i].fontbuf,0,DisplayArea[i].bufsize);
			if(i==1)
			{
				DisplayArea[i].upflag = 1;
				DisplayArea[i].enable = 1;		
				//�ڶ�����ʾ����
				memset(temp,0,sizeof(temp));
				sprintf(temp,"֧���ɹ�"),
				GetFont(temp,8,DisplayArea[1].fontbuf);//��ȡ��ģ��������Ϣ��������fontbuf������					
			}
			else if(i==2)
			{
				DisplayArea[i].upflag = 1;
				DisplayArea[i].enable = 1;		
				//��������ʾ����
				memset(temp,0,sizeof(temp));
				sprintf(temp,"�� ͨ ��"),										
				GetFont(temp,8,DisplayArea[2].fontbuf);//��ȡ��ģ��������Ϣ��������fontbuf������					
			}
			else
			{
				DisplayArea[i].upflag = 0;
				DisplayArea[i].enable = 0;				
			}
		}			
	}
	VoicePlayBack((char*)"֧���ɹ���ף��һ·˳��",22);
}


// ����λ��ͨ�Ŵ����ж�
void USART2_IRQHandler( void )
{
 __IO u8 rcv;
	u8 Clear = 0;
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		UART2_RCV_S.FlagStatus = 1;
		UART2_RCV_S.tick = USART2_RCV_TIME;
		/* Read one byte from the receive data register */
		rcv = USART_ReceiveData(USART2);
		ringBuf_put(rcv);
		//queue_push(rcv);//????BUF????
	}
	//add lbs
	else  if (USART_GetFlagStatus(USART2, USART_FLAG_IDLE) != RESET) {
		Clear = USART2->SR;
		Clear = USART2->DR;
		g_usart2Pack = 1;
	}
	else  if (USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET)//???????'??if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)?????
	{
		USART_ReceiveData(USART2);
		USART_ClearFlag(USART2, USART_FLAG_ORE);
	}
}





























