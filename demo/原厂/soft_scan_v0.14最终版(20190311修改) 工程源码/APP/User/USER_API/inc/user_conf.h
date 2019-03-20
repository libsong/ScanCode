
/********************  ********************
 * �ļ���  ��user_conf.h
 * ����    ��       
 * ����ƽ̨��
 * ��汾  ��ST3.0.0  																										  
 * ��Ŀ���ƣ�
*********************************************************/
#ifndef __USER_CONF_H
#define __USER_CONF_H

//-------�û�ͷ�ļ�----------//
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "stm32f10x_flash.h"
#include "eeprom.h"
#include "malloc.h"

#include "user_usart1.h"//����ͨ�Žӿ�
#include "user_usart2.h"//LED��ʾ��ͨ�Žӿ�
#include "user_usart3.h"//TTSͨ�Žӿ�
#include "user_uart4.h"//�����1ͨ�Žӿ�
#include "user_uart5.h"//�����2ͨ�Žӿ�

#include "user_time.h"
#include "user_delay.h"
#include "use_iap.h"
#include "user_eeprom.h"
#include "user_screen.h"
#include "user_display.h"
#include "user_fontLib.h"
#include "user_cmd_queue.h"
#include "user_scan.h"


//-------�û��궨��----------//
#define  ID_Num  100   //�ն�ϵ�к�
#define  NumWords   4    //4����

#ifdef	 P10
#define  SCREEN_ROW 	2//2����
#else
#define  SCREEN_ROW 	4//4����
#endif

#define USART_RCV_TIME    100  // 40ms  �����ְַ�����
#define USART2_RCV_TIME    3  // ��һ���õ���5MS,�����˷ְ�����

extern uint32_t rowColor[4];
extern uint8_t payMentFlag;//֧����־λ��1����Ч��0����Ч

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

//--------�ⲿ��������-------//



#endif





