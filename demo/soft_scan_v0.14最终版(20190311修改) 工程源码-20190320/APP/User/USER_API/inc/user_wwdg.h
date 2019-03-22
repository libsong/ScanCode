#ifndef __USER_WWDG_H
#define __USER_WWDG_H

#include "stm32f10x_wwdg.h"

//#define IWATCHCDOG_ENABLE                1                                       ///< 0, ���ö������Ź�. 1, ʹ�ܶ������Ź�
#define IWATCHCDOG_TIME_MS              6000                                    ///< �������Ź���λ����ʱ��, ��Чʱ��, 100-26000ms
//#define IWATCHCDOG_VALUE            ((IWATCHCDOG_TIME_MS * 10) / 64) 
/**
  * ���ڿ��Ź�ʱ��Ҫ�����ϸ�, �밴��ʽ���м��� WWATCHDOG_VALUE �� WWATCHDOG_COUNT ��ֵ.
  * ����ֵΪ WWATCHDOG_VALUE = 0x7F, WWATCHDOG_COUNT = 0x7F, ��Чι��ʱ�䴰��Ϊ0ms - 58ms֮��.
  * ����ϵͳĬ��ʱ�� PCLK1 = 36Mhzʱ, ʱ�䴰��(��λΪms)ֵ���㹫ʽ����:
  * WWDG_MAX_MS = 4096 * 8 * (WWATCHDOG_COUNT - 63) / 36000
  * WWDG_MIN_MS = 4096 * 8 * (WWATCHDOG_COUNT - WWATCHDOG_VALUE) / 36000
  * ��Чι��ʱ�䴰�ڼ�Ϊ WWDG_MIN_MS - WWDG_MAX_MS ֮��, ʱ�䵥λΪms
  */
//#define WWATCHDOG_ENABLE                0                                       ///< 0, ���ô��ڿ��Ź�. 1, ʹ�ܴ��ڿ��Ź�
#define WWATCHDOG_COUNT                 0x7F                                    ///< ���ڿ��Ź���������ʼֵ, ��Чֵ, 0x40 - 0x7F
#define WWATCHDOG_VALUE                 0x5F                                    ///< ���ڿ��Ź��������Ƚ�ֵ, ��Чֵ, 0x40 - WWATCHDOG_COUNT

#if IWATCHCDOG_ENABLE
  #if ((IWATCHCDOG_TIME_MS < 100) || (IWATCHCDOG_TIME_MS > 26000))
    #error "IWATCHCDOG_TIME_MS define error!"
  #else
    #define IWATCHCDOG_VALUE            ((IWATCHCDOG_TIME_MS * 10) / 64)        ///< ����������Ź���װ��ֵ, 6.4MSΪ��С��λ
  #endif
#endif

#if WWATCHDOG_ENABLE
  #if ((WWATCHDOG_COUNT < 0x40) || (WWATCHDOG_COUNT > 0x7F))
    #error "WWATCHDOG_COUNT define error!"
  #endif
  #if ((WWATCHDOG_VALUE < 0x40) || (WWATCHDOG_VALUE > WWATCHDOG_COUNT))
    #error "WWATCHDOG_VALUE define error!"
  #endif
#endif

void WatchDogInit(void);                                                        ///< ���Ź���ʼ��
void IWatchDogClear(void);                                                      ///< �������Ź�ι��, ���������ȼ���͵�һ��������ִ��
void WWatchDogClear(void);                                                      ///< ���ڿ��Ź�ι��, ������ڶ�ʱ���ж���ִ��
void WWatchDogDisable(void);                                                    ///< ͣ�ô��ڿ��Ź�. ԭ�����ж���Clock, ʹ�䲻�ټ���. �������ʹ��
#endif

