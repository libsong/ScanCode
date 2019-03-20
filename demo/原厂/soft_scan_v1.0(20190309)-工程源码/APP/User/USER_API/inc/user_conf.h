
/********************  ********************
 * 文件名  ：user_conf.h
 * 描述    ：       
 * 开发平台：
 * 库版本  ：ST3.0.0  																										  
 * 项目名称：
*********************************************************/
#ifndef __USER_CONF_H
#define __USER_CONF_H

//-------用户头文件----------//
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "stm32f10x_flash.h"
#include "eeprom.h"
#include "malloc.h"

#include "user_usart1.h"//调试通信接口
#include "user_usart2.h"//LED显示屏通信接口
#include "user_usart3.h"//TTS通信接口
#include "user_uart4.h"//跟相机1通信接口
#include "user_uart5.h"//跟相机2通信接口

#include "user_time.h"
#include "user_delay.h"
#include "use_iap.h"
#include "user_eeprom.h"
#include "user_screen.h"
#include "user_display.h"
#include "user_fontLib.h"
#include "user_cmd_queue.h"
#include "user_scan.h"


//-------用户宏定义----------//
#define  ID_Num  100   //终端系列号
#define  NumWords   4    //4字屏

#ifdef	 P10
#define  SCREEN_ROW 	2//2行屏
#else
#define  SCREEN_ROW 	4//4行屏
#endif

#define USART_RCV_TIME    100  // 40ms  还出现分包现象
#define USART2_RCV_TIME    3  // 第一次用的是5MS,出现了分包现象。

extern uint32_t rowColor[4];
extern uint8_t payMentFlag;//支付标志位，1：有效，0：无效

#pragma pack(push)
#pragma pack(1)

typedef struct  
{
	uint8_t header;
  uint16_t len;
  uint8_t cmd;
  uint8_t param;
  uint8_t data[CMD_MAX_SIZE];
} TTS_CMD_t;

#pragma pack(pop)

//--------外部数据申明-------//



#endif





