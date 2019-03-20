#ifndef __USART2_H__
#define	__USART2_H__

#include "stm32f10x.h"
#include <stdio.h>
#include "user_conf.h"

#define BMP_DATA_LENGTH	  200//USART1\USART2\���ڽ��ջ��������ȣ��ֽڣ�

void USART2_Config(void);
uint8_t  USART2_Send( char *SendBuff,uint8_t	sendLen );//����8λ�̶�������Ϣ
uint8_t  USART2_SendStr( uint8_t	*SendBuff);//�����ַ�����Ϣ��һ�ַ�����������Ϊ������־
void usart2_rec_timeout(void);
void  SendChar(unsigned char t); 
void SendStrings(unsigned char *str);
void HMI_RS485_Config(void);
void USART2_Rcv(char rcv);
void usart2_rec_timeout(void);

typedef struct  
{
    volatile u8 BmpRecState ; //����״̬
    volatile u8 BmpDataCnt ;  //�����ֽڳ���
    volatile u8 BmpRXLen ;    //������Ϣ֡����
    volatile u8 RcvTimeOut;   //�������ʱ��
//*** �ɹ�����֡��־ ***
    volatile u8 BmpFrameSUc ;   
    volatile u8 Bmp_RX_DataBuf[BMP_DATA_LENGTH] ;
    volatile u8 Process_DataBuf[BMP_DATA_LENGTH];//20���ֽ�
}USART2_Buf_TypeDef;
extern USART2_Buf_TypeDef  USART2_Buf_Struct;


#endif
