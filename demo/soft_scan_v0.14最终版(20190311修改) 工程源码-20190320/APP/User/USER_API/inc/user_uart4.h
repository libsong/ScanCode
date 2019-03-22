#ifndef __USART4_H__
#define	__USART4_H__
#include <stdio.h>
#include "stm32f10x.h"
#include "user_conf.h"

uint8_t  USART4_Send( char *SendBuff,uint8_t	sendLen );//发送8位固定长度信息
uint8_t  USART4_SendStr( uint8_t	*SendBuff);//发送字符串信息以一字符串结束符作为结束标志
void usart4_rec_timeout(void);
void   USART4_BufInit(void);
void USART4_Config(void);

#define USART_RCV_LEN	  200// 
typedef struct  
{
	__IO char buff[USART_RCV_LEN];
	__IO char FlagStatus;//1:开始接收到信号，0没有接收到信号
	__IO char SuccessFlag;
	__IO uint8_t cnt;
	__IO uint32_t tick;
}UART_RCV_T;

extern UART_RCV_T UART4_RCV_S;
extern UART_RCV_T UART5_RCV_S;
extern UART_RCV_T UART1_RCV_S;



#endif

