#ifndef __USER_USART1_H
#define	__USER_USART1_H

#include "stm32f10x.h"
#include <stdio.h>

#include "user_conf.h"
/**************************************************************************************************
 *                                            CONSTANTS
 **************************************************************************************************/
#define RCV_BUF_SIZE 200 

/* Usart Buf structure */
typedef struct {
  uint8_t buf[RCV_BUF_SIZE]; /* The data buffer of usart*/
  uint16_t head;       /* The head index of the data in buffer, point to the last data in the buffer */
  uint16_t tail;          /* The tail index of the data in buffer, point to the first data in the buffer */
  uint16_t max;        /* The max len of the buffer */
  uint16_t cnt;           /* The count of data in the buffer */
  uint32_t rcvCntTotal; /*The total receive count of the port*/
} UsartBuf_t;

void USART1_Config(void);
uint8_t  USART1_Send( char *SendBuff,uint8_t	sendLen );//发送8位固定长度信息
uint8_t  USART1_SendStr( uint8_t	*SendBuff);//发送字符串信息以一字符串结束符作为结束标志
void UART1Test(void);
void USART1_BufInit(void);
void UART_RxCpltCallback(volatile UsartBuf_t * uartBuf, uint8_t rcv);
void USART_InitBuf(volatile UsartBuf_t * uartBuf);
uint8_t USART_WriteBuf(volatile UsartBuf_t * uartBuf, uint8_t data);
uint16_t USART_ReadBuf(volatile UsartBuf_t * uartBuf, uint8_t *buf, uint16_t len);
void u1_printf(const char *format, ...);
void usart1_rec_timeout(void);



#endif


