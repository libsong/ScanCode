#ifndef __USART2_H__
#define	__USART2_H__

#include "stm32f10x.h"
#include <stdio.h>
#include "user_conf.h"

#define BMP_DATA_LENGTH	  200//USART1\USART2\串口接收缓存区长度（字节）

void USART2_Config(void);
uint8_t  USART2_Send( char *SendBuff,uint8_t	sendLen );//发送8位固定长度信息
uint8_t  USART2_SendStr( uint8_t	*SendBuff);//发送字符串信息以一字符串结束符作为结束标志
void usart2_rec_timeout(void);
void  SendChar(unsigned char t); 
void SendStrings(unsigned char *str);
void HMI_RS485_Config(void);
void USART2_Rcv(char rcv);
void usart2_rec_timeout(void);

typedef struct  
{
    volatile u8 BmpRecState ; //接收状态
    volatile u8 BmpDataCnt ;  //接收字节长度
    volatile u8 BmpRXLen ;    //接收信息帧长度
    volatile u8 RcvTimeOut;   //接收最大时间
//*** 成功接收帧标志 ***
    volatile u8 BmpFrameSUc ;   
    volatile u8 Bmp_RX_DataBuf[BMP_DATA_LENGTH] ;
    volatile u8 Process_DataBuf[BMP_DATA_LENGTH];//20个字节
}USART2_Buf_TypeDef;
extern USART2_Buf_TypeDef  USART2_Buf_Struct;


#endif
