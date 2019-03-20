#ifndef __USART3_H
#define	__USART3_H

#include "stm32f10x.h"
#include <stdio.h>
#include "user_conf.h"

#define speakerEnable()         GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_SET)
#define speakerDisable()         GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_RESET)


uint8_t  USART3_Send( char *SendBuff,uint8_t	sendLen );//发送8位固定长度信息
uint8_t  USART3_SendStr( uint8_t	*SendBuff);//发送字符串信息以一字符串结束符作为结束标志
void usart3_rec_timeout(void);
void   USART3_BufInit(void);
void USART3_Config(void);



#endif

