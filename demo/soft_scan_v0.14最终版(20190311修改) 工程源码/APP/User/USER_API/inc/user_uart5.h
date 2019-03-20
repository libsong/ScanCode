#ifndef __USART5_H
#define	__USART5_H

#include "stm32f10x.h"
#include <stdio.h>
#include "user_conf.h"


uint8_t  USART5_Send( char *SendBuff,uint8_t	sendLen );//发送8位固定长度信息
uint8_t  USART5_SendStr( uint8_t	*SendBuff);//发送字符串信息以一字符串结束符作为结束标志
void usart5_rec_timeout(void);
void   USART5_BufInit(void);
void USART5_Config(void);



#endif

