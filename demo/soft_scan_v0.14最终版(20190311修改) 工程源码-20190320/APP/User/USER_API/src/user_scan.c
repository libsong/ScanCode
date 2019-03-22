#include "user_conf.h"
#include "user_time.h"

uint32_t uart2BaudRate = 9600;//串口2通信波特率


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

//控制扫码头启动扫码及关闭扫码功能
//参数：cmd:  ENABLE 开始扫码命令，Disable  停止扫码命令。
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



//DisplayArea[i].mode显示模式

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
//#define MOVE_LEFTSTATIC 0x01   //静态左移动，宽度太大左滚动
//#define MOVE_UPSTATIC  	0x02     //静态上移动，高度太大上滚动
//#define MOVE_CLEAR  	  0xff
//首页显示
void FirstPage(void)
{
	unsigned char i;	
	char temp[40]={0};
	//出厂默认设置
	//出厂默认初始化分区，区域1、2、3、4，
	for(i=0;i<4;i++)
	{
		DisplayArea[i].y= i*16;//区域纵坐标起始点
		DisplayArea[i].x= 0;//区域横坐标起始点
		DisplayArea[i].h= 16;//区域高度（像素点）。
		DisplayArea[i].w= 64;//区域宽度（像素点）。
		DisplayArea[i].type = 0;//显示类型，0显示字符，1，显示图片
		DisplayArea[i].mode = 0;//0:静态显示,1,静态左移动，宽度太大左滚动，2: //静态上移动，高度太大上滚动
		DisplayArea[i].speed = 2;//取值范围（0-6）
		DisplayArea[i].col = 0;//显示颜色，0：红色，1：绿色
		
		DisplayArea[i].movexx =0;//清零
		DisplayArea[i].movex =0;//清零
		DisplayArea[i].moveyy =0;//清零
		DisplayArea[i].movey =0;//清零
		DisplayArea[i].bufsize =0;//清零
		Screen.col = DisplayArea[i].col;
		DisplayArea[i].enable =1;
		if(DisplayArea[i].fontbuf != NULL)
		{
			myfree(DisplayArea[i].fontbuf);//释放分区缓存	
			DisplayArea[i].fontbuf = NULL;
		}
		//显示内容
		DisplayArea[i].fh= 16;//该区域实际显示数据高度，如果1行16，如果两行32，三行48,4行64
		DisplayArea[i].fw= 64;//该区域实际显示数据宽度，一个汉字为16个，一个字符为8.
		DisplayArea[i].bufsize = (((DisplayArea[i].fh>>4)*(DisplayArea[i].fw>>3))<<4);//5个汉字 需要160个字节的空间
		DisplayArea[i].fontbuf = mymalloc(DisplayArea[i].bufsize);	
		if(DisplayArea[i].fontbuf !=0)
		{
			mymemset(DisplayArea[i].fontbuf,0,DisplayArea[i].bufsize);
			DisplayArea[i].upflag = 1;
			DisplayArea[i].enable = 1;		
			if(i==0)
			{
				memset(temp,0,sizeof(temp));
				sprintf(temp,"欢迎使用"),
				GetFont(temp,8,DisplayArea[0].fontbuf);//获取字模，点阵信息都保存在fontbuf里面了							
			}
			else if(i==1)
			{
				//第二行显示内容
				memset(temp,0,sizeof(temp));
				sprintf(temp,"山西高速"),
				GetFont(temp,8,DisplayArea[1].fontbuf);//获取字模，点阵信息都保存在fontbuf里面了					
			}
			else if(i==2)
			{
				//第三行显示内容
				memset(temp,0,sizeof(temp));
				sprintf(temp,"扫码支付"),										
				GetFont(temp,8,DisplayArea[2].fontbuf);//获取字模，点阵信息都保存在fontbuf里面了					
			}
			else if(i==3)
			{
				//第四行显示内容
				memset(temp,0,sizeof(temp));
				sprintf(temp,"自助终端"),															
				GetFont(temp,8,DisplayArea[3].fontbuf);//获取字模，点阵信息都保存在fontbuf里面了				
			}
		}			
	}
}
//支付页面显示
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
	//出厂默认设置
	//出厂默认初始化分区，区域1、2、3、4，
	for(i=0;i<4;i++)
	{
		DisplayArea[i].y= i*16;
		DisplayArea[i].x= 0;
		DisplayArea[i].h= 0x10;//ScreenArea->h
		DisplayArea[i].w= 0x40;
		DisplayArea[i].type = 0;//显示字符
		DisplayArea[i].mode = 0;//静态显示
		DisplayArea[i].speed = 2;//取值范围（0-6）
		
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
			myfree(DisplayArea[i].fontbuf);//释放分区缓存	
			DisplayArea[i].fontbuf = NULL;
		}
		//显示内容
		DisplayArea[i].fh= 16;
		DisplayArea[i].fw= 64;			
		DisplayArea[i].bufsize = (((DisplayArea[i].fh>>4)*(DisplayArea[i].fw>>3))<<4);//5个汉字 需要160个字节的空间
		DisplayArea[i].fontbuf = mymalloc(DisplayArea[i].bufsize);	
		if(DisplayArea[i].fontbuf !=0)
		{
			mymemset(DisplayArea[i].fontbuf,0,DisplayArea[i].bufsize);
			if(i==1)
			{
				DisplayArea[i].upflag = 1;
				DisplayArea[i].enable = 1;		
				//第二行显示内容
				memset(temp,0,sizeof(temp));
				sprintf(temp,"支付成功"),
				GetFont(temp,8,DisplayArea[1].fontbuf);//获取字模，点阵信息都保存在fontbuf里面了					
			}
			else if(i==2)
			{
				DisplayArea[i].upflag = 1;
				DisplayArea[i].enable = 1;		
				//第三行显示内容
				memset(temp,0,sizeof(temp));
				sprintf(temp,"请 通 行"),										
				GetFont(temp,8,DisplayArea[2].fontbuf);//获取字模，点阵信息都保存在fontbuf里面了					
			}
			else
			{
				DisplayArea[i].upflag = 0;
				DisplayArea[i].enable = 0;				
			}
		}			
	}
	VoicePlayBack((char*)"支付成功，祝您一路顺风",22);
}


// 跟上位机通信串口中断
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





























