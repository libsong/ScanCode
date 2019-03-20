#ifndef __USER_WWDG_H
#define __USER_WWDG_H

#include "stm32f10x_wwdg.h"

//#define IWATCHCDOG_ENABLE                1                                       ///< 0, 禁用独立看门狗. 1, 使能独立看门狗
#define IWATCHCDOG_TIME_MS              6000                                    ///< 独立看门狗复位近似时间, 有效时间, 100-26000ms
//#define IWATCHCDOG_VALUE            ((IWATCHCDOG_TIME_MS * 10) / 64) 
/**
  * 窗口看门狗时间要求及其严格, 请按公式自行计算 WWATCHDOG_VALUE 和 WWATCHDOG_COUNT 的值.
  * 建议值为 WWATCHDOG_VALUE = 0x7F, WWATCHDOG_COUNT = 0x7F, 有效喂狗时间窗口为0ms - 58ms之间.
  * 采用系统默认时钟 PCLK1 = 36Mhz时, 时间窗口(单位为ms)值计算公式如下:
  * WWDG_MAX_MS = 4096 * 8 * (WWATCHDOG_COUNT - 63) / 36000
  * WWDG_MIN_MS = 4096 * 8 * (WWATCHDOG_COUNT - WWATCHDOG_VALUE) / 36000
  * 有效喂狗时间窗口即为 WWDG_MIN_MS - WWDG_MAX_MS 之间, 时间单位为ms
  */
//#define WWATCHDOG_ENABLE                0                                       ///< 0, 禁用窗口看门狗. 1, 使能窗口看门狗
#define WWATCHDOG_COUNT                 0x7F                                    ///< 窗口看门狗计数器初始值, 有效值, 0x40 - 0x7F
#define WWATCHDOG_VALUE                 0x5F                                    ///< 窗口看门狗计数器比较值, 有效值, 0x40 - WWATCHDOG_COUNT

#if IWATCHCDOG_ENABLE
  #if ((IWATCHCDOG_TIME_MS < 100) || (IWATCHCDOG_TIME_MS > 26000))
    #error "IWATCHCDOG_TIME_MS define error!"
  #else
    #define IWATCHCDOG_VALUE            ((IWATCHCDOG_TIME_MS * 10) / 64)        ///< 计算独立看门狗的装填值, 6.4MS为最小单位
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

void WatchDogInit(void);                                                        ///< 看门狗初始化
void IWatchDogClear(void);                                                      ///< 独立看门狗喂狗, 建议在优先级最低的一个任务中执行
void WWatchDogClear(void);                                                      ///< 窗口看门狗喂狗, 建议放在定时器中断中执行
void WWatchDogDisable(void);                                                    ///< 停用窗口看门狗. 原理是切断其Clock, 使其不再计数. 特殊情况使用
#endif

