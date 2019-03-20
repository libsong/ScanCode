#ifndef __USE_IAP1_H
#define	__USE_IAP1_H

#include "stm32f10x.h"
#include <stdio.h>


/* Exported types ------------------------------------------------------------*/
typedef  void (*pFunction)(void);

/* Exported constants --------------------------------------------------------*/
/* Constants used by Serial Command Line Mode */

#define FLASH_IMAGE_SIZE  (uint32_t) (FLASH_SIZE - (ApplicationAddress - 0x08000000))
#define FramLen            64           //√ø÷° ˝æ›≥§∂»
#define IAP_DOWN_MAX_Cyc   100//√ø÷°◊Ó¥Û—≠ª∑∑¢ÀÕ¥Œ ˝
#define IAP_Repeat_Num     10 //÷ÿ∑¢º‰∏Ù¥Œ ˝
#define Delay_Fram         40 // √ø÷°º‰∏Ù ±º‰40MS
#define IAP_DOWN_SIZE      28 //œ¬‘ÿµƒFALSH¥Û–°  µ•ŒªKB
#define CMD_STRING_SIZE       128

#define ApplicationAddress    0x8003000
#define IAPAddress   0x8000000
#define User_Flash (ApplicationAddress-PAGE_SIZE)//IAPµƒ◊Ó∫Û“ª“≥”√¿¥¥Ê¥¢”√ªß–≈œ¢°£
#if defined (STM32F10X_MD) || defined (STM32F10X_MD_VL)
#define PAGE_SIZE                         (0x800)    /* 2 Kbyte *///“—æ≠∂®“Â¡À
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
#define ADDR_FLASH_LAST_PAGE               (0x8000000+FLASH_SIZE-PAGE_SIZE)//¥Ê¥¢”√ªßœ˚œ¢°£

/* Compute the FLASH upload image size */  


#pragma pack(push) //±£¥Ê∂‘∆Î∑Ω Ω
#pragma pack(1)	//∞¥◊÷Ω⁄∂‘∆
typedef struct 
{
    uint16_t Fram_Nmb;//÷°∫≈
    uint32_t data[FramLen/4] ;//÷° ˝æ›
    
}Down_StructDef;
#pragma pack(pop) //ª÷∏¥∂‘∆Î∑Ω Ω

typedef struct 
{
    uint8_t Start_Piont[4];//∆Ù∂Øµ„£¨0£∫±Ì æ…œµÁ∆Ù∂Ø£¨1£∫±Ì æ¥”APPÃ¯◊™π˝¿¥°£
    uint8_t Down_Wait_Flag;//œ¬‘ÿ±Í÷æŒª£¨1£∫±Í÷æ¥¶”⁄œ¬‘ÿ◊¥Ã¨°£∆‰À˚£∫±Ì æ∑«œ¬‘ÿ◊¥Ã¨°£
    uint8_t Flash_Type;//falsh¥Û–°
    uint8_t iap_downFlag;
    uint32_t ID_Num11;//÷’∂À–Ú¡–∫≈
    
}IAP_StructDef;

extern IAP_StructDef IAP_StructExtern;
extern __IO uint32_t IAP_Tick;  
void APP_Jump_IAP(void);
void IAP_DataInit(void);

#endif



