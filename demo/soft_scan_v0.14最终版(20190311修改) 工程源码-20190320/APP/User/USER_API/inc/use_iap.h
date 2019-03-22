#ifndef __USE_IAP1_H
#define	__USE_IAP1_H

#include "stm32f10x.h"
#include <stdio.h>


/* Exported types ------------------------------------------------------------*/
typedef  void (*pFunction)(void);

/* Exported constants --------------------------------------------------------*/
/* Constants used by Serial Command Line Mode */

#define FLASH_IMAGE_SIZE  (uint32_t) (FLASH_SIZE - (ApplicationAddress - 0x08000000))
#define FramLen            64           //ÿ֡���ݳ���
#define IAP_DOWN_MAX_Cyc   100//ÿ֡���ѭ�����ʹ���
#define IAP_Repeat_Num     10 //�ط��������
#define Delay_Fram         40 // ÿ֡���ʱ��40MS
#define IAP_DOWN_SIZE      28 //���ص�FALSH��С  ��λKB
#define CMD_STRING_SIZE       128

#define ApplicationAddress    0x8003000
#define IAPAddress   0x8000000
#define User_Flash (ApplicationAddress-PAGE_SIZE)//IAP�����һҳ�����洢�û���Ϣ��
#if defined (STM32F10X_MD) || defined (STM32F10X_MD_VL)
#define PAGE_SIZE                         (0x800)    /* 2 Kbyte *///�Ѿ�������
#define FLASH_SIZE                        (0x10000)  /*64k //128 KBytes */
#elif defined STM32F10X_CL
#define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
#define FLASH_SIZE                        (0x40000)  /* 256 KBytes */
#elif defined STM32F10X_HD || defined (STM32F10X_HD_VL)
#define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
#define FLASH_SIZE                        (0x80000)  /* 512 KBytes */
#elif defined STM32F10X_XL
#define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
#define FLASH_SIZE                        (0x100000) /* 1 MByte */
#else 
#error "Please select first the STM32 device to be used (in stm32f10x.h)"    
#endif
#define ADDR_FLASH_LAST_PAGE               (0x8000000+FLASH_SIZE-PAGE_SIZE)//�洢�û���Ϣ��

/* Compute the FLASH upload image size */  


#pragma pack(push) //������뷽ʽ
#pragma pack(1)	//���ֽڶ��
typedef struct 
{
    uint16_t Fram_Nmb;//֡��
    uint32_t data[FramLen/4] ;//֡����
    
}Down_StructDef;
#pragma pack(pop) //�ָ����뷽ʽ

typedef struct 
{
    uint8_t Start_Piont[4];//�����㣬0����ʾ�ϵ�������1����ʾ��APP��ת������
    uint8_t Down_Wait_Flag;//���ر�־λ��1����־��������״̬����������ʾ������״̬��
    uint8_t Flash_Type;//falsh��С
    uint8_t iap_downFlag;
    uint32_t ID_Num11;//�ն����к�
    
}IAP_StructDef;

extern IAP_StructDef IAP_StructExtern;
extern __IO uint32_t IAP_Tick;  
void APP_Jump_IAP(void);
void IAP_DataInit(void);

#endif



