#ifndef __DISPLAY_H
#define __DISPLAY_H
#include "stdint.h"

#define ARROW_LEFTTURN  6
#define ARROW_RIGHTTURN  7
#define ARROW_RIGHTUP  5
#define ARROW_LEFTUP  	4
#define ARROW_LEFT  	2
#define ARROW_RIGHT  	3
#define ARROW_UP  		0
#define ARROW_DOWN  	1

#define MOVE_STATIC  	  0x0
#define MOVE_UPIN  		  0x11
#define MOVE_UPOUT  	  0x12
#define MOVE_UPCYC  	  0x13
#define MOVE_LEFTIN  		0x21
#define MOVE_LEFTOUT    0x22
#define MOVE_LEFTCYC    0x23
#define MOVE_RIGHTIN		0x31
#define MOVE_RIGHTOUT		0x32
#define MOVE_RIGHTCYC		0x33

#define MOVE_DOWN		    0x43
#define MOVE_LEFTUP   	0x53
#define MOVE_RIGHTUP  	0x63
#define MOVE_LEFTSTATIC 0x01   //静态左移动，宽度太大左滚动
#define MOVE_UPSTATIC  	0x02     //静态上移动，高度太大上滚动
#define MOVE_CLEAR  	  0xff

#define DISPLAY_AREA_MAX  10

//P75 口控制线定义
//#define DAT75_H()    GPIOE->BSRR  = 1<<0
//#define DAT75_L()    GPIOE->BRR  	= 1<<0
//#define EN75_H()     GPIOB->BSRR  = 1<<3
//#define EN75_L()     GPIOB->BRR   = 1<<3

//#define LA75_H()     GPIOB->BSRR  = 1<<4
//#define LA75_L()     GPIOB->BRR  	= 1<<4

//#define CLK75_H()    GPIOB->BSRR  = 1<<9
//#define CLK75_L()    GPIOB->BRR  	= 1<<9

//#define P75_Off() 	EN75_H()
//#define P75_On() 		EN75_L()

//#define LED_OFF()	  P75_Off()
//#define LED_ON()	 	P75_On()


#define MAX_BUFSIZE	(12*1024) 	//分配4k存储空间
#define MAX_8  (50+30)				//每行最多50个汉字

#pragma anon_unions

typedef struct _SCREEN_
{
	unsigned char enable;
	unsigned char col;   //显示颜色 
	unsigned short kh;    // 多少个16像素高
	unsigned short kw;    //多少个8像素宽
	unsigned short size;
	unsigned char *disbuff;  
	unsigned char *screenbuff;  
	unsigned short offset;
}SCREEN;


typedef struct _DISPLAY_
{
	unsigned char enable; 
	unsigned char upflag; //更新标志
	unsigned char type;
	unsigned char col;//区域颜色
	unsigned char y;
	unsigned char x;
	unsigned char h;
	unsigned char w;
	unsigned char fh;
	unsigned char fw;
	unsigned char mode;
	short movey;   //滚动变量
	short movex;
	short moveyy;  //轮滚变量
	short movexx;
	unsigned short speed;
	unsigned short bufsize;
	unsigned short speedcnt; // 
	unsigned char *UinCode;
	unsigned char *fontbuf; //缓存字库
}DISPLAY;



void mdelay(int ms);
void moveL(void);
void InitLedPin(void);
void LEDTest(void);

void LedDisplayInit(void);

long screen_shell(int argc,char **argv);

void printled(const unsigned char *led, int len);
void DisplayLeftProcess(DISPLAY *display);
void DisplayRightProcess(DISPLAY *display);
void DisplayUpProcess(DISPLAY *display);
void DisplayStaticProcess(DISPLAY *display);
void DisplayDownProcess(DISPLAY *display);
void DisplayLeftUpProcess(DISPLAY *display);
void DisplayRightUpProcess(DISPLAY *display);
void DisplayMoveProcess(DISPLAY *display,short x,short y);
void DisplayInitArrow(uint8_t y,uint8_t x,uint8_t h,uint8_t w,unsigned char arrow,uint8_t mode);
void DisplayProcess(DISPLAY *Display);
void DisplayInitStr(uint8_t y,uint8_t x,uint8_t h,uint8_t w,uint8_t fh,uint8_t fw,unsigned char *str,uint8_t mode);
void DisplayInitCarCnt(uint8_t y,uint8_t x,unsigned short cnt,uint8_t bitcnt);
void DisplayLeftStaticProcess(DISPLAY *display);
void DisplayUpStaticProcess(DISPLAY *display);
void DisplayInitStr1(uint8_t y,uint8_t x,uint8_t h,uint8_t w,uint8_t fh,uint8_t fw,unsigned char *str,uint8_t mode);
void displayTask(void);
void DisplayClearProcess(DISPLAY *display);
void ScreenDisplayProcess(void);   //
extern void disTiming(void);



extern uint8_t disDelayFlag  ;
extern uint8_t	disDelyaTime  ;


#endif
