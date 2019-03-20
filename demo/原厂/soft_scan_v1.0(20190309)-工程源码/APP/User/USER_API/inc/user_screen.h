#ifndef SCREEN_H
#define SCREEN_H


#pragma pack(push)//保存对齐状态 
#pragma pack(1)  //设置为1字节对齐


typedef struct __SCREEN_AREA
{
	unsigned char id; 
	unsigned char col;
	unsigned char x;	   
	unsigned char y;
	unsigned char w;
	unsigned char h;
}SCREEN_AREA;

typedef struct __AREA_DISPLAY
{
	unsigned char id; 
	unsigned char type;  //区域显示类型  0:字符 1:图形 
	unsigned char mode;
	unsigned char speed;
	unsigned char fw;
	unsigned char fh;
}AREA_DISPLAY;

typedef union __SCREEN_CTR_DATA
{
	
	SCREEN_AREA  ScreenArea;
	AREA_DISPLAY AreaDisplay;
}SCREEN_CTR_DATA;

typedef struct __SCREEN_CTR_HEAD
{
	unsigned char len;    //数据体长度
	unsigned char cmd;   // 0x00:区域设置 0x01:区域显示
	SCREEN_CTR_DATA CtrData;
}SCREEN_CTR_HEAD;

#pragma pack(pop)


void ScreenInit(void);
void ScreenSend(unsigned char *dat,unsigned short len);
unsigned short ScreenRev(unsigned char *dat,unsigned short timeout);
unsigned short ScreenRevCnt(unsigned char *dat,unsigned short len,unsigned short timeout);
void ScreenCtrScan(void);
unsigned int ScreenRevProcess(unsigned char *buf);
void ScreenScan(void);//tim2
void senddata(unsigned char i);
char VoicePlayBack(char *data,unsigned char len);
void PaymentPage(void);
void FirstPage(void);

void ScreenTask(void);

#define SETA GPIOB->BSRR=1<<9
#define CLRA GPIOB->BRR=1<<9
#define SETB GPIOB->BSRR=1<<8
#define CLRB GPIOB->BRR=1<<8
#define SETC GPIOB->BSRR=1<<7
#define CLRC GPIOB->BRR=1<<7
#define SETD GPIOB->BSRR=1<<6
#define CLRD GPIOB->BRR=1<<6
#define SETE GPIOE->BSRR=1<<0
#define CLRE GPIOE->BRR=1<<0

#define _DAT77_OH()    GPIOB->BSRR  = 1<<3
#define _DAT77_OL()     GPIOB->BRR  = 1<<3

#define _DAT77_R1H()    GPIOE->BSRR  = 1<<6
#define _DAT77_R1L()     GPIOE->BRR  	= 1<<6
#define _DAT77_G1H()    GPIOE->BSRR  = 1<<5
#define _DAT77_G1L()     GPIOE->BRR  	= 1<<5
#define _DAT77_B1H()    GPIOE->BSRR  = 1<<4
#define _DAT77_B1L()     GPIOE->BRR  	= 1<<4
#define _DAT77_R2H()    GPIOE->BSRR  = 1<<3
#define _DAT77_R2L()     GPIOE->BRR  	= 1<<3
#define _DAT77_G2H()    GPIOE->BSRR  = 1<<2
#define _DAT77_G2L()     GPIOE->BRR  	= 1<<2
#define _DAT77_B2H()    GPIOE->BSRR  = 1<<1
#define _DAT77_B2L()     GPIOE->BRR  	= 1<<1

#define _DAT77_CH()    GPIOB->BSRR  = 1<<5
#define _DAT77_CL()     GPIOB->BRR  	= 1<<5

#define _DAT77_LH()    GPIOB->BSRR  = 1<<4
#define _DAT77_LL()     GPIOB->BRR  	= 1<<4


#define EN75_H()     GPIOB->BSRR  = 1<<3
#define EN75_L()     GPIOB->BRR   = 1<<3
#define P75_Off() 	EN75_H()
#define P75_On() 	EN75_L()
#define LED_OFF()	P75_Off()
#define LED_ON()	 	P75_On()
#endif



