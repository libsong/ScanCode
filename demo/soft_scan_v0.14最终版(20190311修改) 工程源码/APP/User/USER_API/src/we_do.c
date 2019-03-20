#include <stdio.h>
#include "user_conf.h"

#define DEVID 1 //标识生产的第 n 台设备 生产时考虑其他方式获取，如硬件存储

#define PACKDATASIZE 32

#define HEARTBEAT_CYCLE 10000 //10s
#define DATAPACK_HEADTAIL 0X2A

volatile u8 g_usart2Pack = 0;
volatile unsigned long long sysIntCnt = 0;
u8 host2Scan = 0;
extern volatile unsigned long long scanWaitTimeCnt;

struct dataPack {
	u8 head;
	u8 len;
	u8 cmd;
	u8 data[PACKDATASIZE];
	u8 crc;
	u8 tail;
};

#define RINGBUFSIZE (128*2)
struct my_fifo {
	unsigned char *buffer; /* the buffer holding the data*/
	unsigned int size; /* the size of the allocated buffer*/
	unsigned int in; /* data is added at offset (in % size)*/
	unsigned int out; /* data is extracted from off. (out % size)*/
};
struct my_fifo 	*g_ptrRecv = NULL;

extern void scanCodeCtrl(uint8_t cmd);
extern char VoicePlayBack(char *data,unsigned char len);
extern void PaymentPage(void);
extern void FirstPage(void);
extern DISPLAY DisplayArea[];
extern SCREEN Screen;

void dataPack(u8 cmd, u8 origin[], int len, u8 packed[])
{
	int i;
	int idx = 0;
	u8 crc = 0;
	
	//head len cmd data crc tail
	packed[idx++] = DATAPACK_HEADTAIL;
	packed[idx++] = len;
	packed[idx++] = cmd;
	
	for (i=0; i<len; i++) {
		packed[3+i] = origin[i];
		crc += origin[i];		
		idx++;
	}	
	
	packed[idx++] = crc;
	packed[idx] = DATAPACK_HEADTAIL;
	
	return ;
}

void heartBeat (void)
{
	static u8 first = 0;
	u8 beat[5] ;
	u8 beatP[32];
	
	if (first == 0) {//避免   第一包总是少头 0x2a 后续都正常
		first = 1;
		beatP[0] = 0;
		USART2_Send((char *)beatP, 1);	
	}
	if (sysIntCnt % HEARTBEAT_CYCLE == 0) {//第一包总是少头 0x2a 后续都正常
		beat[0] = 0x00;
		beat[1] = 0x00;
		beat[2] = 0x00;
		beat[3] = 0x00;
		beat[4] = 0x00;
		dataPack(0x05,beat,5,beatP);
		USART2_Send((char *)beatP, 10);		
	}	
	
	return ;
}

void DevSN (u8 sn[], u32 devCnt)
{
	u8 Sn[9] = {'A','A','A','A','A','A','A','A','A'};
	int i;
	int idx = 0;
	
	sn[0] = 'A';
	sn[1] = 'D';
	
	for (i=2; i<9; i++) {
		sn[i] = Sn[i];
	}
}

//
//
//ring buf
//
//

/*
 * min()/max() macros that also do
 * strict type-checking.. See the
 * "unnecessary" pointer comparison.
 */
#define min(a,b) ((a) < (b) ? (a):(b))

//?in==out?,????????,?(in-out)==size ?,???????
 /*

my_fifo_init

 */
struct my_fifo *my_fifo_init(unsigned char *buffer, unsigned int size)
{
	struct my_fifo *fifo;

	fifo = malloc(sizeof(struct my_fifo));
	if (!fifo)
		return NULL;

	fifo->buffer = buffer;
	fifo->size = size;
	fifo->in = fifo->out = 0;

	return fifo;
}

/*
 my_fifo_alloc
*/
struct my_fifo *my_fifo_alloc(unsigned int size)
{
	unsigned char *buffer;
	struct my_fifo *ret;
	/*
	* round up to the next power of 2, since our 'let the indices
	* wrap' tachnique works only in this case.
	*/

	buffer = malloc(size);
	if (!buffer)
		return NULL;

	ret = my_fifo_init(buffer, size);
	if (ret == NULL)
		free(buffer);

	return ret;
}
/*
* my_fifo_free
*/
void my_fifo_free(struct my_fifo *fifo)
{
	free(fifo->buffer) ;
	free(fifo) ;
}

/*
 my_fifo_put()
 */
unsigned int my_fifo_put(struct my_fifo *fifo, unsigned char *buffer, unsigned int len)
{
	unsigned int l ;

	len = min(len, (fifo->size - fifo->in + fifo->out)); /*?????????????????*/

	/* first put the data starting from fifo->in to buffer end*/
	l = min(len, fifo->size - (fifo->in & (fifo->size - 1))) ;
	memcpy(fifo->buffer + (fifo->in & (fifo->size - 1)), buffer, l) ;

	/* then put the rest (if any) at the beginning of the buffer*/
	memcpy(fifo->buffer, buffer + l, len - l) ;

	fifo->in += len ;

	return len ;
}

 
 /*
 my_fifo_get
 */
unsigned int my_fifo_get(struct my_fifo *fifo, unsigned char *buffer, unsigned int len)
{
	unsigned int l ;

	len = min(len, fifo->in - fifo->out); /*????*/

	/* first get the data from fifo->out until the end of the buffer*/
	l = min(len, fifo->size - (fifo->out & (fifo->size - 1)));
	memcpy(buffer, fifo->buffer + (fifo->out & (fifo->size - 1)), l) ;

	/* then get the rest (if any) from the beginning of the buffer*/
	memcpy(buffer + l, fifo->buffer, len - l) ;

	fifo->out += len ;

	return len ;
}

void my_fifo_reset(struct my_fifo *fifo)
{
	fifo->in = fifo->out = 0 ;
}
 
unsigned int my_fifo_len(struct my_fifo *fifo)
{
	return fifo->in - fifo->out ;
}

int ringBuf_init(void)
{
	g_ptrRecv = my_fifo_alloc(RINGBUFSIZE);
	if (g_ptrRecv == NULL) {
		return -1;
	}
	return 0;
}

void ringBuf_put(u8 data)
{
	my_fifo_put(g_ptrRecv,&data,1);
}

void WePage(u8 data[],int len)
{
	u8 weTmp[16];
	
	unsigned char i;	
	char temp[40]={0};
 	
	memset(weTmp,' ',16);
	memcpy(weTmp,data,len);
	
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
			if (i == 0 || i== 1) {
				DisplayArea[i].upflag = 1;
				DisplayArea[i].enable = 1;		
				memset(temp,0,sizeof(temp));
				//sprintf(temp,"支付成功"),
				memcpy(temp,&weTmp[i*8],8);
				GetFont(temp,8,DisplayArea[i].fontbuf);//获取字模，点阵信息都保存在fontbuf里面了			
			}
			else {
				DisplayArea[i].upflag = 0;
				DisplayArea[i].enable = 0;	
			}
		}			
	}
}

void voicePut (u8 cmd) 
{
	int tmp = cmd;
	
	switch (tmp) {
		case 0:
			VoicePlayBack((char*)"支付成功",8);
				WePage((u8*)"支付成功",8);
			break;
		case 1:
			VoicePlayBack((char *)"支付失败",8);
				WePage((u8*)"支付失败",8);
		break;
		case 2:
			VoicePlayBack((char *)"余额不足",8);
		WePage((u8*)"余额不足",8);
			break;
		case 3:
			VoicePlayBack((char *)"密码错误",8);
				WePage((u8*)"密码错误",8);
		break;
		case 4:
			VoicePlayBack((char *)"订单撤销",8);
				WePage((u8*)"订单撤销",8);
		break;
		case 5:
			VoicePlayBack((char *)"支付码失效",10);
				WePage((u8*)"支付码失效",10);
		break;
		case 6:
			VoicePlayBack((char *)"支付码无效",10);
				WePage((u8*)"支付码无效",10);
		break;
		case 7:
			VoicePlayBack((char *)"等待交易",8);
				WePage((u8*)"等待交易",8);
		break;
		case 8:
			VoicePlayBack((char *)"请出示支付码",12);
				WePage((u8*)"请出示支付码",12);
		break;
		case 9:
			VoicePlayBack((char *)"正在交易",8);
		WePage((u8*)"正在交易",8);	
		break;		
		
		default:
			break;
	}
}

void ClearPage()
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
				DisplayArea[i].upflag = 0;
				DisplayArea[i].enable = 0;
				//DisplayArea[i].upflag = 1;
				//DisplayArea[i].enable = 1;		
				//第二行显示内容
				//memset(temp,0,sizeof(temp));
				//sprintf(temp,"支付成功"),
				//GetFont(temp,8,DisplayArea[1].fontbuf);//获取字模，点阵信息都保存在fontbuf里面了					
			}
			else if(i==2)
			{
				DisplayArea[i].upflag = 0;
				DisplayArea[i].enable = 0;
				//DisplayArea[i].upflag = 1;
				//DisplayArea[i].enable = 1;		
				//第三行显示内容
				//memset(temp,0,sizeof(temp));
				//sprintf(temp,"请 通 行"),										
				//GetFont(temp,8,DisplayArea[2].fontbuf);//获取字模，点阵信息都保存在fontbuf里面了					
			}
			else
			{
				DisplayArea[i].upflag = 0;
				DisplayArea[i].enable = 0;				
			}
		}			
	}
}

void scanCodeSend (void) 
{
	char data[64];
	char pack[64];
	
	DevSN((u8 *)data,DEVID);
	memcpy(&data[9],(void *)UART5_RCV_S.buff,UART5_RCV_S.cnt);
	dataPack(4,(u8 *)data,9+UART5_RCV_S.cnt,(u8 *)pack);
	
	USART2_Send((char *)pack,9+UART5_RCV_S.cnt+5);
}

void scanCodeTimeOut (void)
{
	u8 dataTimeOut[27];
	u8 pack[64];
	int i;
	
	memset(dataTimeOut,0,27);
	dataTimeOut[0] = 'D';
	dataTimeOut[1] = 'A';
	dataTimeOut[2] = 'D';
	dataTimeOut[3] = 'A';
	dataPack(4,dataTimeOut,27,pack);
	
	USART2_Send((char *)pack,27+5);
	VoicePlayBack((char*)"等待扫码超时",12);
}

void doWeTask(void)
{
	struct dataPack tmp;
	int len,i,cmd;
	u8 crc = 0;
	
	len = my_fifo_len(g_ptrRecv);
	if (len >= 5) {
		my_fifo_get(g_ptrRecv,&tmp.head,1);
		my_fifo_get(g_ptrRecv,&tmp.len,1);
		my_fifo_get(g_ptrRecv,&tmp.cmd,1);
		my_fifo_get(g_ptrRecv,tmp.data,tmp.len);
		my_fifo_get(g_ptrRecv,&tmp.crc,1);
		my_fifo_get(g_ptrRecv,&tmp.tail,1);
	}
	else {
		return ;
	}
	
	if (tmp.head != 0x2A || tmp.tail != 0x2A) {
		return ;
	}
	for (i=0; i<tmp.len; i++) {
		crc = crc + tmp.data[i];
	}
	if (crc != tmp.crc) {
		return ;
	}
	
	cmd = tmp.cmd;
	switch (cmd) {
		case 1://模组开关
			//scanCodeCtrl(tmp.data[0]);//加上此函数则使用 2A 01 01 01 01 2A 开模组，串口调试助手会收到一个 0xFF
			if (tmp.data[0] == 1) {
				host2Scan = 1;
				scanWaitTimeCnt = 1;
			}
			break;
		case 2://语音
			voicePut(tmp.data[0]);
			break;
		case 3://显示
			WePage(tmp.data,tmp.len);
			break;
		
		default:
			break;
	}
	
	return ;
}

//for
//Error: L6915E: Library reports error: __use_no_semihosting was requested, but _ttywrch was referenced
int _ttywrch(int ch)
{
	ch = ch;
	return 0;
}








