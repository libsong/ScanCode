#ifndef __USE_IAP1_H
#define	__USE_IAP1_H

#include "stm32f10x.h"
#include <stdio.h>


/* Exported types ------------------------------------------------------------*/
typedef  void (*pFunction)(void);

/* Exported constants --------------------------------------------------------*/
/* Constants used by Serial Command Line Mode */

#define FLASH_IMAGE_SIZE  (uint32_t) (FLASH_SIZE - (ApplicationAddress - 0x08000000))
#define FramLen            64           //每帧数据长度
#define IAP_DOWN_MAX_Cyc   100//每帧最大循环发送次数
#define IAP_Repeat_Num     10 //重发间隔次数
#define Delay_Fram         40 // 每帧间隔时间40MS
#define IAP_DOWN_SIZE      28 //下载的FALSH大小  单位KB
#define CMD_STRING_SIZE       128

#define ApplicationAddress    0x8003000
#define IAPAddress   0x8000000
#define User_Flash (ApplicationAddress-PAGE_SIZE)//IAP的最后一页用来存储用户信息。
#if defined (STM32F10X_MD) || defined (STM32F10X_MD_VL)
#define PAGE_SIZE                         (0x800)    /* 2 Kbyte *///已经定义了
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
#define ADDR_FLASH_LAST_PAGE               (0x8000000+FLASH_SIZE-PAGE_SIZE)//存储用户消息。

/* Compute the FLASH upload image size */  


#pragma pack(push) //保存对齐方式
#pragma pack(1)	//按字节对�
typedef struct 
{
    uint16_t Fram_Nmb;//帧号
    uint32_t data[FramLen/4] ;//帧数据
    
}Down_StructDef;
#pragma pack(pop) //恢复对齐方式

typedef struct 
{
    uint8_t Start_Piont[4];//启动点，0：表示上电启动，1：表示从APP跳转过来。
    uint8_t Down_Wait_Flag;//下载标志位，1：标志处于下载状态。其他：表示非下载状态。
    uint8_t Flash_Type;//falsh大小
    uint8_t iap_downFlag;
    uint32_t ID_Num11;//终端序列号
    
}IAP_StructDef;

extern IAP_StructDef IAP_StructExtern;
extern __IO uint32_t IAP_Tick;  
void APP_Jump_IAP(void);
void IAP_DataInit(void);

#endif



